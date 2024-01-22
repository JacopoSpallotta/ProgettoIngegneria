#ifndef endog_glucose_prod
#define endog_glucose_prod

#include "patient.h"

using namespace std;

double EGP(double kp1, insulin_kinetics_old ins_old, glucose_kinetics_old old_gluc, endog_glucose_prod_old old_end);
double X_L(endog_glucose_prod_old old);
double I_f (insulin_kinetics_old ins_old, endog_glucose_prod_old end_old);


#endif