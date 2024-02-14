#include "main.h"
using namespace std;

insulin_pump_state next(Insulin_Pump& pump, redisContext *c2r, int curr_t, int *read_counter){

    if (pump.state == test){
        redisReply *reply = RedisCommand(c2r, "XREADGROUP GROUP diameter insulin_pump COUNT 1 BLOCK 1000000000 NOACK STREAMS %s >", READ_STREAM);
        
        char *gluc = new char[64];
        ReadStreamMsgVal(reply,0,0,1,gluc);
        (*read_counter)++;
        double glucose_level = stod(gluc);
        delete gluc;

        double curr_delta = glucose_level - pump.prev_glucose;
        double old_delta = pump.prev_glucose - pump.prev_prev_glucose;
        pump.t_old = curr_t;
        

        if(glucose_level >= SAFE_MIN_GLUCOSE && glucose_level <= SAFE_MAX_GLUCOSE){
            if(glucose_level > pump.prev_glucose && (curr_delta >= old_delta)){
                pump.comp_dose = round(curr_delta/4.0);

                if(pump.comp_dose == 0){
                    pump.comp_dose = 2; // MINDOSE
                }
                return execution;

            }else{
                pump.comp_dose = 0;
                return execution;
            }
        } else if (glucose_level < SAFE_MIN_GLUCOSE){
            pump.comp_dose = 0;
            return execution;

        } else if (glucose_level > SAFE_MAX_GLUCOSE){
            if (glucose_level > pump.prev_glucose){
                pump.comp_dose = round(curr_delta/4.0);

                if(pump.comp_dose <= 0){
                    pump.comp_dose = 2; // MINDOSE
                }
                return execution;

            }else if(glucose_level == pump.prev_glucose){
                pump.comp_dose = 2; // MINDOSE
                return execution;

            }else if(glucose_level < pump.prev_glucose && curr_delta > old_delta){
                pump.comp_dose = 2; // MINDOSE
                return execution;
            }else{
                pump.comp_dose = 0;
                return execution;
            }
        }

        pump.prev_prev_glucose = pump.prev_glucose;
        pump.prev_glucose = glucose_level;
        freeReplyObject(reply);
    }
    if(pump.state == idle){
        if( (curr_t - pump.t_old) > 5){
            return test;
        }
        return idle;
    }
    if(pump.state == execution){
        cout<<"Dose: "<<pump.comp_dose<<endl;
        redisReply *reply = RedisCommand(c2r, "XADD %s * %s %f", WRITE_STREAM, "dose", pump.comp_dose);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        freeReplyObject(reply);
        return idle;
    }
}