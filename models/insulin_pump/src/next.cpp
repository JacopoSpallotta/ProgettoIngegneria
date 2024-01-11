#include "main.h"
using namespace std;

insulin_pump_state next(Insulin_Pump pump, redisContext *c2r, int curr_t){
    if (pump.state == test){
        printf("main(): pid %d: insulin_pump: Trying to read msg from stream %s\n", getpid(), READ_STREAM);

        redisReply *reply = RedisCommand(c2r, "XREADGROUP GROUP diameter insulin_pump COUNT 1 NOACK STREAMS %s >", READ_STREAM);

        assertReply(c2r, reply);
        double glucose_level = stod(reply->str);
        double prev_glucose = pump.prev_glucose;

        double delta = glucose_level-prev_glucose;
        pump.t_old = curr_t;
        if(delta > 10){
            return execution;
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

    }
}