#ifndef main_h
#define main_h

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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

#define READ_STREAM "stream1"
#define WRITE_STREAM "stream2"
#define ENV_STREAM "stream3"
#define DEBUG 0

#endif