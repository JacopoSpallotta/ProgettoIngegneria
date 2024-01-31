#include "main.h"
using namespace std;

insulin_pump_state next(Insulin_Pump pump, redisContext *c2r, int curr_t, int *read_counter){

    if (pump.state == test){
        printf("main(): pid %d: insulin_pump: Trying to read msg %d from stream %s\n", getpid(), *read_counter, READ_STREAM);
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
                    pump.comp_dose = 1; // MINDOSE
                }
                return execution;

            }else{
                return idle;
            }
        } else if (glucose_level < SAFE_MIN_GLUCOSE){
            return idle;
            // ALERT STATE?
        } else if (glucose_level > SAFE_MAX_GLUCOSE){
            if (glucose_level > pump.prev_glucose){
                pump.comp_dose = round(curr_delta/4.0);
                if(pump.comp_dose == 0){
                    pump.comp_dose = 1; // MINDOSE
                }
                return execution;

            }else if(glucose_level == pump.prev_glucose){
                pump.comp_dose = 1; // MINDOSE
                return execution;

            }else if(glucose_level < pump.prev_glucose && curr_delta > old_delta){
                pump.comp_dose = 1; // MINDOSE
                return execution;
            }else{
                return idle;
            }
        }

        freeReplyObject(reply);
    }
    if(pump.state == idle){
        redisReply *reply = RedisCommand(c2r, "XADD %s * %s -1", WRITE_STREAM, "dose");
        //printf("main(): pid =%d: stream %s: Added %s -> %f (id: %s)\n", getpid(), WRITE_STREAM, "dose", pump.comp_dose, reply->str);
        freeReplyObject(reply);
        if( (curr_t - pump.t_old) > 5000){
            return test;
        }
        return idle;
    }
    if(pump.state == execution){
        redisReply *reply = RedisCommand(c2r, "XADD %s * %s %f", WRITE_STREAM, "dose", pump.comp_dose);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        //printf("main(): pid =%d: stream %s: Added %s -> %f (id: %s)\n", getpid(), WRITE_STREAM, "dose", pump.comp_dose, reply->str);
        freeReplyObject(reply);
        return idle;
    }
}