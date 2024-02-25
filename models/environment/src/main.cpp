#include "main.h"

using namespace std;


int main() {
    redisContext *c2r;
    redisReply *reply;
    int pid = getpid();
    unsigned seed;
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

    printf("main(): pid %d: user insulin_pump: connecting to redis ...\n", pid);

    c2r = redisConnect("localhost", 6379);

    printf("main(): pid %d: user insulin_pump: connected to redis\n", pid);

    // Delete streams if exists

    reply = RedisCommand(c2r, "DEL %s", WRITE_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    /* Create streams/groups */
    initStreams(c2r, WRITE_STREAM);

    // Create and connect to database
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    init_logdb(db, pid);

    long nseconds = 0;
    
    int t = 0;
    int delta = 0;
    log2db(db, pid, nseconds, t, delta);

    while (t <= 2*MINUTES_PER_DAY){
        long nseconds_diff = get_curr_nsecs() - nseconds;
        if( (t % (MEAL_DURATION+FASTING_DURATION) >= 0) && (t % (MEAL_DURATION+FASTING_DURATION) < MEAL_DURATION)){
            delta = 1;
        }else{
            delta = 0;
        }

        redisReply *reply = RedisCommand(c2r, "XADD %s * %s %d", WRITE_STREAM, "isEating", delta);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        freeReplyObject(reply);

        t++;
        log2db(db, pid, nseconds_diff, t, delta);
        usleep(10000);

    }  // while ()
    
    redisFree(c2r);
}

long get_curr_nsecs(){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ( (long) (ts.tv_sec * 1000000000L + ts.tv_nsec));
}
