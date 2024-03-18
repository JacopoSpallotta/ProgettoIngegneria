#include "main.h"

using namespace std;


int main() {
    
    redisContext *c2r;
    redisReply *reply;
    int pid = getpid();
    unsigned seed;

    struct time time_p = {0};

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
    reply = RedisCommand(c2r, "DEL %s", PATIENT_TO_PUMP);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    reply = RedisCommand(c2r, "DEL %s", PUMP_TO_PATIENT);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    /* Create streams/groups */
    initStreams(c2r, PATIENT_TO_PUMP);
    initStreams(c2r, PUMP_TO_PATIENT);

    // Create and connect to database
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    init_logdb(db, pid);

    long nseconds = 0;
    
    Insulin_Pump pump = {test,GLUCOSE_INIT,100,100};
    char time_str[13];
    time_db(&time_p, &time_str[0]);
    log2db(db, pid, nseconds, time_str, pump.state, 0);

    while (get_time(&time_p) <= MINUTES_PER_DAY){
        long nseconds_diff = get_curr_nsecs() - nseconds;
        double comp_dose = 0;
        if(pump.state == compute_release){
            comp_dose = compute_dose(pump.prev_prev_glucose, pump.prev_glucose, pump.glucose_level);
        }
        insulin_pump_state next_state = next(pump, c2r, get_time(&time_p), &time_p, comp_dose);
        pump.state = next_state;
        
        update_time(&time_p);
        time_db(&time_p, &time_str[0]);
        log2db(db, pid, nseconds_diff, time_str, pump.state, comp_dose);
        
        usleep(1000*T);
    }  // while ()

    redisFree(c2r);
}


long get_curr_nsecs(){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ( (long) (ts.tv_sec * 1000000000L + ts.tv_nsec));
}
