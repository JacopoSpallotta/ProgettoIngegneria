#ifndef main_h
#define main_h

#include "con2redis.h"
#include "pgsql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "insulin_pump.h"
#include "log2db.h"
#include "init_db.h"

#define READ_STREAM "stream2"
#define WRITE_STREAM "stream1"
#define DEBUG 1000000000
#define SAFE_MIN_GLUCOSE 80
#define HARD_MIN_GLUCOSE 50
#define SAFE_MAX_GLUCOSE 100
#define HARD_MAX_GLUCOSE 120

insulin_pump_state next(Insulin_Pump pump, redisContext* c2r, int curr_t, int* read_counter);
long get_curr_nsecs();
#endif