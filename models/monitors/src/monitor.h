#ifndef monitor_h
#define monitor_h

#include "pgsql.h"
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include "my_time.h"

#define MINUTES_PER_DAY 1440

void monitor_safety(Con2DB* db, struct m_safety* m_safety, double gluc_val);
void monitor_liveness(Con2DB* db,  struct m_liveness* m_liveness, double gluc_val);
void monitor_minimalDose(Con2DB* db,  struct m_minDose* m_minDose, int comp_dose);

struct m_safety{
    int tuples_read;
    struct time time_p;
};

struct m_liveness{
    int tuples_read;
    double gluc_sum;
    struct time time_p;
};

struct m_minDose{
    int tuples_read;
    int daily_dose;
    struct time time_p;
};

using namespace std;

#endif