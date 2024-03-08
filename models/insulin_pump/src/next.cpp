#include "main.h"
using namespace std;

insulin_pump_state next(Insulin_Pump& pump, redisContext *c2r, double curr_t, int *read_counter, struct time* time_p){

    if (pump.state == test){
        redisReply *reply = RedisCommand(c2r, "XREADGROUP GROUP diameter insulin_pump COUNT 1 BLOCK 1000000000 NOACK STREAMS %s >", PATIENT_TO_PUMP);
        char *gluc = new char[64];
        ReadStreamMsgVal(reply,0,0,1,gluc);
        (*read_counter)++;
        double glucose_level = stod(gluc);
        delete gluc;
        freeReplyObject(reply);

        double curr_delta = glucose_level - pump.prev_glucose;
        double old_delta = pump.prev_glucose - pump.prev_prev_glucose;
        cout<<"T: "<<curr_t<<"["<<endl;
        cout<<"\tCurr_delta: "<<curr_delta<<endl;
        cout<<"\tOld_delta: "<<old_delta<<endl;
        cout<<"\tGlucose_level: "<<glucose_level<<endl;
        cout<<"\tPrev_glucose: "<<pump.prev_glucose<<endl;
        cout<<"\tPrev_prev_glucose: "<<pump.prev_prev_glucose<<endl;
        cout<<"\tSum_insulin: "<<pump.sum_insulin<<endl;
        cout<<"]\n"<<endl;

        if (glucose_level >= HARD_MAX_GLUCOSE){
            pump.comp_dose = round((glucose_level-TARGET_GLUCOSE)/4);
            pump.prev_prev_glucose = pump.prev_glucose;
            pump.prev_glucose = glucose_level;
            return execution;

        } else if(glucose_level >= SAFE_MIN_GLUCOSE && glucose_level <= SAFE_MAX_GLUCOSE){
            if(glucose_level > pump.prev_glucose && (curr_delta >= old_delta)){
                pump.comp_dose = round((glucose_level-TARGET_GLUCOSE)/1.5);

                if(pump.comp_dose <= 0){
                    pump.comp_dose = MINDOSE;
                }
                pump.prev_prev_glucose = pump.prev_glucose;
                pump.prev_glucose = glucose_level;
                return execution;
            }else{
                pump.comp_dose = 0;
                pump.prev_prev_glucose = pump.prev_glucose;
                pump.prev_glucose = glucose_level;
                return execution;
            }
        } else if (glucose_level < SAFE_MIN_GLUCOSE){
            pump.comp_dose = 0;
            pump.prev_prev_glucose = pump.prev_glucose;
            pump.prev_glucose = glucose_level;
            return execution;

        } else if (glucose_level > SAFE_MAX_GLUCOSE){
            if (glucose_level > pump.prev_glucose){
                pump.comp_dose = round((glucose_level-TARGET_GLUCOSE)/2);

                if(pump.comp_dose <= 0){
                    pump.comp_dose = MINDOSE;
                }
                pump.prev_prev_glucose = pump.prev_glucose;
                pump.prev_glucose = glucose_level;
                return execution;

            }else if(glucose_level == pump.prev_glucose ){
                pump.comp_dose = MINDOSE;
                pump.prev_prev_glucose = pump.prev_glucose;
                pump.prev_glucose = glucose_level;
                return execution;

            }else if(glucose_level < pump.prev_glucose && curr_delta > old_delta ){
                pump.comp_dose = MINDOSE;
                pump.prev_prev_glucose = pump.prev_glucose;
                pump.prev_glucose = glucose_level;
                return execution;
            }else{
                pump.comp_dose = 0;
                pump.prev_prev_glucose = pump.prev_glucose;
                pump.prev_glucose = glucose_level;
                return execution;
            }
        }
        
    }
    if(pump.state == idle){
        if( check_time(time_p, TEST_TIME, 0)){
            return test;
        }
        return idle;
    }
    if(pump.state == execution){
        cout<<"Dose: "<<pump.comp_dose<<endl;
        pump.sum_insulin += pump.comp_dose;
        redisReply *reply = RedisCommand(c2r, "XADD %s * %s %f", PUMP_TO_PATIENT, "dose", pump.comp_dose);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        freeReplyObject(reply);
        return idle;
    }
}