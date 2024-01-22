#ifndef rate_glucose_app
#define rate_glucose_app

#include "patient.h"
#include <cmath>

using namespace std;

double Alpha (double dose);
double Beta (double dose);
double K_empt(double q_sto, double dose);
double Q_sto(rate_glucose_app_old g_app_old);
double Q_sto_1(rate_glucose_app_old g_app_old, double dose, int delta);
double Q_sto_2(rate_glucose_app_old g_app_old, double dose);
double Q_gut(rate_glucose_app_old g_app_old, double dose);
double Ra_meal (rate_glucose_app_old g_app_old, double bw);

#endif