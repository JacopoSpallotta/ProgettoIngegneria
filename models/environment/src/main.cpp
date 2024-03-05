#include "main.h"

using namespace std;


int main() {
    redisContext *c2r;
    redisReply *reply;
    int pid = getpid();
    unsigned seed;

    struct time time_p = {0};
    /*
    printf("%d\n",pid);
    int ciao = 0;
    while(ciao == 0){
        sleep(5);
    }*/
    /*  prg  */

    #if (DEBUG > 0)
    setvbuf(stdout, (char*) NULL, _IONBF, 0);
    setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif

    seed = (unsigned) time(NULL);
    srand(seed);

    pid = getpid();

    printf("main(): pid %d: user environment: connecting to redis ...\n", pid);

    c2r = redisConnect("localhost", 6379);

    printf("main(): pid %d: user environment: connected to redis\n", pid);

    // Delete streams if exists

    reply = RedisCommand(c2r, "DEL %s", ENV_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    reply = RedisCommand(c2r, "DEL %s", DUMMY_ENV_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    /* Create streams/groups */
    initStreams(c2r, ENV_STREAM);
    initStreams(c2r, DUMMY_ENV_STREAM);

    // Create and connect to database
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    init_logdb(db, pid);

    long nseconds = 0;
    
    int delta = 0;
    char time_str[13];
    time_db(&time_p, &time_str[0]);
    log2db(db, pid, nseconds, time_str, delta);

    while (get_time(&time_p) <= 2*MINUTES_PER_DAY){
        long nseconds_diff = get_curr_nsecs() - nseconds;
        int minute = floor(get_time(&time_p));
        if( (minute % (MEAL_DURATION+FASTING_DURATION) >= 0) && (minute % (MEAL_DURATION+FASTING_DURATION) < MEAL_DURATION)){
            delta = 1;
        }else{
            delta = 0;
        }

        redisReply *reply = RedisCommand(c2r, "XADD %s * %s %d", ENV_STREAM, "isEating", delta);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        freeReplyObject(reply);

        update_time(&time_p);
        time_db(&time_p, time_str);
        log2db(db, pid, nseconds_diff, time_str, delta);

        // dummy comms with patient to synchronize patient and environment
        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter environment COUNT 1 BLOCK 10000000000 NOACK STREAMS %s >", DUMMY_ENV_STREAM);
        freeReplyObject(reply);

        usleep(10000*T);

    }  // while ()
    
    redisFree(c2r);
}

long get_curr_nsecs(){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ( (long) (ts.tv_sec * 1000000000L + ts.tv_nsec));
}
