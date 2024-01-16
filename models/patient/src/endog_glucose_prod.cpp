#include "main.h"
#include "patient.h"
#include "glucose_kinetics.cpp"
#include "insulin_kinetics.cpp"

using namespace std;


double EGP(endog_glucose_prod_old old, int t){
    double Gpb = Gb*Vg;
    double Ipb = Ib*Vi;
    double m30 = (Heb*m1) / (double) (1-Heb);
    double HEb= (SRb - m4*Ipb) / (double) (SRb+m2*Ipb);
    double Ilb = (Ipb*m2 + SRb)/ (double)(m1+m30);

    double kp1 = EGPb+kp2*Gpb+kp3*Ib+kp4*Ilb;

    double curr_egp = old.egp + T * (kp1- kp2*G_p(t) - kp3*X_L(old, t) - kp4*I_l(t)); // TODO: verificare t=0 cosa fare (?)
    old.egp = curr_egp;
    return curr_egp;
}

double X_L(endog_glucose_prod_old old, int t){
    double x_curr = old.x_l + T * (-ki * (old.x_l - I_f(old, t)));
    old.x_l = x_curr;
    return x_curr;
}

double I_f (endog_glucose_prod_old old, int t){
    double i_curr = -ki * (old.i_f - I(t));
    old.i_f = i_curr;
    return i_curr;
}