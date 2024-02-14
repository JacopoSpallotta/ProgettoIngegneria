#ifndef main_h
#define main_h

#include "con2redis.h"
#include "pgsql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include "log2db.h"
#include "init_db.h"
#define DEBUG 0

#define WRITE_STREAM "stream3"

long get_curr_nsecs();

using namespace std;


#endif