#include "main.h"

using namespace std;



int main() {
    redisContext *c2r;
    redisReply *reply;
    int read_counter = 0;
    int send_counter = 0;
    long block = 100000000000;
    int pid;
    unsigned seed;
    char username[100];
    char key[100];
    char value[100];

    
    /*  prg  */

    #if (DEBUG > 0)
    setvbuf(stdout, (char*) NULL, _IONBF, 0);
    setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif

    seed = (unsigned) time(NULL);
    srand(seed);

    sprintf(username, "%u", rand());

    pid = getpid();

    printf("main(): pid %d: user %s: connecting to redis ...\n", pid, username);

    c2r = redisConnect("localhost", 6379);

    printf("main(): pid %d: user %s: connected to redis\n", pid, username);

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
        insulin_pump_state next_state = next(pump, c2r, t);
        
        t++;
        usleep(10000);

        /* sleep   */
        //micro_sleep(1000000);
    }  // while ()
    
    redisFree(c2r);
}
