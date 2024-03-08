#include "my_time.h"

void update_time(struct time* curr_time){
    curr_time -> minutes += T;
}

double get_time(struct time* curr_time){
    return curr_time -> minutes;
}

bool check_time(struct time* curr_time, int min, int target){
    double epsilon = pow(10,-5);
    // eliminate double imprecision: if the curr minutes is a double like 5.99999999999998 take the rounded one
    // otherwise take the original
    double minutes = (abs(round(curr_time -> minutes) - curr_time -> minutes) <= epsilon) ? round(curr_time -> minutes) : curr_time -> minutes;
    double modulo = fmod(minutes, min);

    // check if modulo is small enough; example: if target is 0 and modulo is 0.0000000000000098 due to double imprecision,
    // return true still
    return modulo <= (epsilon + target) && modulo >= (target-epsilon);
}

void time_db(struct time* curr_time, char* time_str){
    tm t{};
    double minutes;
    double decimal = modf(curr_time -> minutes, &minutes);
    int hours = (int) minutes / 60;
    int minutes_mod = (int) minutes % 60;
    int milliseconds_temp = decimal * (1000 * 60);
    int seconds = milliseconds_temp / 1000;

    t.tm_hour = hours;
    t.tm_min = minutes_mod;
    t.tm_sec = seconds;
    int milliseconds = milliseconds_temp - (seconds*1000);

    char milli_str[5];
    sprintf(milli_str, ".%d",milliseconds);

    strftime(time_str, 9, "%H:%M:%S", &t);
    strcat(time_str, milli_str);
}