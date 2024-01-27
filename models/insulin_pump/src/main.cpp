#include "main.h"

using namespace std;


int main() {
    redisContext *c2r;
    redisReply *reply;
    int read_counter = 0;
    int pid = getpid();
    unsigned seed;
    
    /*  prg  */

    #if (DEBUG > 0)
    setvbuf(stdout, (char*) NULL, _IONBF, 0);
    setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif

    seed = (unsigned) time(NULL);
    srand(seed);

    pid = getpid();

    printf("main(): pid %d: user insulin_pump: connecting to redis ...\n", pid);

    c2r = redisConnect("localhost", 6379);

    printf("main(): pid %d: user insulin_pump: connected to redis\n", pid);

    // Delete streams if exists
    reply = RedisCommand(c2r, "DEL %s", READ_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    reply = RedisCommand(c2r, "DEL %s", WRITE_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    /* Create streams/groups */
    initStreams(c2r, READ_STREAM);
    initStreams(c2r, WRITE_STREAM);
    
    int t = 0;
    Insulin_Pump pump = {HARD_MIN_GLUCOSE,SAFE_MIN_GLUCOSE,HARD_MAX_GLUCOSE,SAFE_MAX_GLUCOSE,test,0.0,0};

    while (1){
        insulin_pump_state next_state = next(pump, c2r, t, &read_counter);
        pump.state = next_state;
        
        t++;
        usleep(10000);

        /* sleep   */
        //micro_sleep(1000000);
    }  // while ()
    
    redisFree(c2r);
}
