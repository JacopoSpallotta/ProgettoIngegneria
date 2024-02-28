#ifndef monitor_h
#define monitor_h

#include "pgsql.h"
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>

void monitor_safety(Con2DB* db, struct m_safety* m_safety);
void monitor_liveness(Con2DB* db,  struct m_liveness* m_liveness);
void monitor_minimalDose(Con2DB* db,  struct m_minDose* m_minDose)

struct m_safety{
    int tuples_read;
};

struct m_liveness{
    int tuples_read;
    double gluc_sum;
};

struct m_minDose{
    int tuples_read;
};

using namespace std;

#endif