#ifndef main_h
#define main_h

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include "con2redis.h"
#include "pgsql.h"
#include "c_peptide_kinetics.h"
#include "endog_glucose_prod.h"
#include "glucose_kinetics.h"
#include "insulin_cpeptide.h"
#include "insulin_kinetics.h"
#include "rate_glucose_app.h"
#include "renal_excretion.h"
#include "glucose_utilization.h"
#include "init_db.h"
#include "log2db.h"
#include "my_time.h"

#define PUMP_TO_PATIENT "stream1"
#define PATIENT_TO_PUMP "stream2"
#define ENV_STREAM "stream3"
#define DUMMY_ENV_STREAM "stream4"
#define DEBUG 0
#define TEST_TIME 10
#define MINUTES_PER_DAY 1440
#define G_FNAME "../../../python-scripts/glucose_data.csv"
#define I_FNAME "../../../python-scripts/insulin_data.csv"

long get_curr_nsecs();

#endif