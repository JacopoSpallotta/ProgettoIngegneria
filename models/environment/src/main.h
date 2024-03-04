#ifndef main_h
#define main_h

#include "con2redis.h"
#include "pgsql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include "log2db.h"
#include "init_db.h"
#include "my_time.h"
#define DEBUG 0
#define MINUTES_PER_DAY 1440
#define MEAL_DURATION 60
#define FASTING_DURATION 480

#define ENV_STREAM "stream3"
#define DUMMY_ENV_STREAM "stream4"

long get_curr_nsecs();

using namespace std;


#endif