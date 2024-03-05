#ifndef time_h
#define time_h

#include <math.h>
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <iostream>

const double T = 0.1;

void time_db(struct time* curr_time, char* time_str);

void update_time(struct time* curr_time);

double get_time(struct time* curr_time);

bool check_time(struct time* curr_time, int min, int target);

struct time {
    double minutes;
};

using namespace std;

#endif