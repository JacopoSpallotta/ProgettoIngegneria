#include "endog_glucose_prod.h"

// A9
double EGP(double kp1, insulin_kinetics_old ins_old, glucose_kinetics_old old_gluc, endog_glucose_prod_old old_end){
    double curr_egp = (kp1- kp2*old_gluc.G_p - kp3*old_end.x_l - kp4*ins_old.I_l);
    return curr_egp;
}

// A10
double X_L(endog_glucose_prod_old old){
    double x_curr = old.x_l + T * (-ki * (old.x_l - old.i_f));
    return x_curr;
}

// A11
double I_f (insulin_kinetics_old ins_old, endog_glucose_prod_old end_old){
    double i_curr = end_old.i_f + T * (-ki * (end_old.i_f - ins_old.I));
    return i_curr;
}