#include "my_time.h"

void update_time(struct time* curr_time){
    curr_time -> minutes += T;
}

double get_time(struct time* curr_time){
    return curr_time -> minutes;
}

bool check_time(struct time* curr_time, int min){
    double curr_mins = curr_time -> minutes;
    if(curr_mins == floor(curr_mins)){
        return !((int) curr_mins % min);
    }
    return false;
}

void time_db(struct time* curr_time, char* time_str){
    tm t{};
    double minutes;
    double decimal = modf(curr_time -> minutes, &minutes);
    int hours = (int) minutes / 60;
    int milliseconds_temp = decimal * (1000 * 60) * T;
    int seconds = milliseconds_temp / 1000;

    t.tm_hour = hours;
    t.tm_min = (int)minutes;
    t.tm_sec = seconds;
    int milliseconds = milliseconds_temp - (seconds*1000);

    char milli_str[5];
    sprintf(milli_str, ".%d",milliseconds);

    strftime(time_str, 9, "%H:%M:%S", &t);
    strcat(time_str, milli_str);
}