#ifndef glucose_kinetics
#define glucose_kinetics

#include "patient.h"
#include "main.h"

using namespace std;

double G(glucose_kinetics_old g_old);
double G_t(glucose_kinetics_old g_old, glucose_utilization_old util_old);
double G_p(glucose_kinetics_old g_old, endog_glucose_prod_old end_old, rate_glucose_app_old rate_old, glucose_utilization_old util_old, renal_exrection_old ren_old);


#endif