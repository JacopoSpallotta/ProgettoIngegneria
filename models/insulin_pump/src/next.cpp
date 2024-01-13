#include "main.h"
using namespace std;

insulin_pump_state next(Insulin_Pump pump, redisContext *c2r, int curr_t){
    double compDose = 0.0;

    if (pump.state == test){
        printf("main(): pid %d: insulin_pump: Trying to read msg from stream %s\n", getpid(), READ_STREAM);

        redisReply *reply = RedisCommand(c2r, "XREADGROUP GROUP diameter insulin_pump COUNT 1 BLOCK 1000000000 NOACK STREAMS %s >", READ_STREAM);

        assertReply(c2r, reply);
        double glucose_level = stod(reply->str);

        double curr_delta = glucose_level - pump.prev_glucose;
        double old_delta = pump.prev_glucose - pump.prev_prev_glucose;

        pump.t_old = curr_t;
        if(glucose_level >= SAFE_MIN_GLUCOSE && glucose_level <= SAFE_MAX_GLUCOSE){
            if(glucose_level > pump.prev_glucose && (curr_delta >= old_delta)){
                compDose = round(curr_delta/4.0);

                if(compDose == 0){
                    compDose = 1; // MINDOSE
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
                compDose = round(curr_delta/4.0);
                if(compDose == 0){
                    compDose = 1; // MINDOSE
                }
                return execution;

            }else if(glucose_level == pump.prev_glucose){
                compDose = 1; // MINDOSE
                return execution;

            }else if(glucose_level < pump.prev_glucose && curr_delta > old_delta){
                compDose = 1; // MINDOSE
                return execution;

            }else{
                return idle;
            }
        }

        freeReplyObject(reply);
    }
    if(pump.state == idle){
        if( (curr_t - pump.t_old) > 50){
            return test;
        }
        return idle;
    }
    if(pump.state == execution){
        redisReply *reply = RedisCommand(c2r, "XADD %s * %s %f", WRITE_STREAM, "dose", compDose);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        printf("main(): pid =%d: stream %s: Added %s -> %f (id: %s)\n", getpid(), WRITE_STREAM, "dose", compDose, reply->str);
        freeReplyObject(reply);
    }
}