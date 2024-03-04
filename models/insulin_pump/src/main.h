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
#include "my_time.h"

#define PATIENT_TO_PUMP "stream2"
#define PUMP_TO_PATIENT "stream1"
#define DEBUG 0
#define SAFE_MIN_GLUCOSE 90
#define HARD_MIN_GLUCOSE 50
#define SAFE_MAX_GLUCOSE 110
#define HARD_MAX_GLUCOSE 120
#define TEST_TIME 10
#define TARGET_GLUCOSE 100
#define MINDOSE 1
#define MINUTES_PER_DAY 1440

insulin_pump_state next(Insulin_Pump& pump, redisContext* c2r, double curr_t, int* read_counter, struct time*);
long get_curr_nsecs();
#endif