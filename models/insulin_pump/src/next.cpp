#include "main.h"
using namespace std;

insulin_pump_state next(Insulin_Pump& pump, redisContext *c2r, double curr_t, struct time* time_p, double comp_dose){

    if (pump.state == test){
        redisReply *reply = RedisCommand(c2r, "XREADGROUP GROUP diameter insulin_pump COUNT 1 BLOCK 1000000000 NOACK STREAMS %s >", PATIENT_TO_PUMP);
        char *gluc = new char[64];
        ReadStreamMsgVal(reply,0,0,1,gluc);
        double glucose_level = stod(gluc);
        delete gluc;
        freeReplyObject(reply);

        pump.prev_prev_glucose = pump.prev_glucose;
        pump.prev_glucose = pump.glucose_level;
        pump.glucose_level = glucose_level;

        return compute_release;
    }else if(pump.state == idle){
        if( check_time(time_p, TEST_TIME, 0)){
            return test;
        }
        return idle;
    }else {
        redisReply *reply = RedisCommand(c2r, "XADD %s * %s %f", PUMP_TO_PATIENT, "dose", comp_dose);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        freeReplyObject(reply);
        return idle;
    }
}

double compute_dose(double prev_prev_glucose, double prev_glucose, double glucose_level){
    double curr_delta = glucose_level - prev_glucose;
    double old_delta = prev_glucose - prev_prev_glucose;
    double comp_dose = 0;

    if (glucose_level >= HARD_MAX_GLUCOSE){
        comp_dose = round((glucose_level-TARGET_GLUCOSE));

        if(comp_dose <= 0){
            comp_dose = MINDOSE;
        }

    } else if (glucose_level > SAFE_MAX_GLUCOSE){
        if (glucose_level > prev_glucose){
            comp_dose = round((glucose_level-TARGET_GLUCOSE));

            if(comp_dose <= 0){
                comp_dose = MINDOSE;
            }
        }else if( (glucose_level == prev_glucose) || (glucose_level < prev_glucose && curr_delta > old_delta)){
            comp_dose = MINDOSE;
        }

    } else if(glucose_level >= SAFE_MIN_GLUCOSE && glucose_level <= SAFE_MAX_GLUCOSE){
        if(glucose_level > prev_glucose && (curr_delta >= old_delta)){
            comp_dose = round((glucose_level-TARGET_GLUCOSE));

            if(comp_dose <= 0){
                comp_dose = MINDOSE;
            }
        }
    }

    if (comp_dose > 9){
        comp_dose = 9;
    }

    return comp_dose;
}