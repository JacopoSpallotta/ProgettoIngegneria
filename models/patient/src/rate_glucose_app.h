#ifndef rate_glucose_app
#define rate_glucose_app

#include "patient.h"
#include "main.h"

using namespace std;

double Alpha (double dose);
double Beta (double dose);
double K_empt(double q_sto, double dose);
double Q_sto(rate_glucose_app_old g_app_old);
double Q_sto_1(double dose, int delta, rate_glucose_app_old g_app_old);
double Q_sto_2(double dose, rate_glucose_app_old g_app_old);
double Q_gut(double dose, rate_glucose_app_old g_app_old);
double Ra_meal (double bw, rate_glucose_app_old g_app_old);
#endif