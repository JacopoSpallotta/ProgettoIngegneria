#include "main.h"
#include "patient.h"
#include "glucose_kinetics.cpp"
#include "insulin_kinetics.cpp"

using namespace std;

// A9
double EGP(insulin_kinetics_old ins_old, glucose_kinetics_old old_gluc, endog_glucose_prod_old old_end){
    double Gpb = Gb*Vg;
    double Ipb = Ib*Vi;
    double m30 = (Heb*m1) / (double) (1-Heb);
    double HEb= (SRb - m4*Ipb) / (double) (SRb+m2*Ipb);
    double Ilb = (Ipb*m2 + SRb)/ (double)(m1+m30);

    double kp1 = EGPb+kp2*Gpb+kp3*Ib+kp4*Ilb;

    double curr_egp = old_end.egp + T * (kp1- kp2*old_gluc.G_p - kp3*old_end.x_l - kp4*ins_old.I_l); // TODO: verificare t=0 cosa fare (?)
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