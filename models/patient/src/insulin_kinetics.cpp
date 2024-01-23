#include "insulin_kinetics.h"

// A2
double I(insulin_kinetics_old ins_old, double u){
    double curr_i = (ins_old.I_p + u)/Vi;
    return curr_i;
}

// A2
double I_ev(insulin_kinetics_old ins_old){
    double curr_i_ev = ins_old.I_ev + T * ( -m6 * ins_old.I_ev + m5 * ins_old.I_p );
    return curr_i_ev;
}

// A2
double I_p(insulin_kinetics_old ins_old, double u){
    double curr_i_p = ins_old.I_p + T * ( ( -(m2+m4+m5)*ins_old.I_p + m1*ins_old.I_l + m6*ins_old.I_ev ) + u );
    return curr_i_p;
}

// A2
double I_l(insulin_kinetics_old ins_old, insulin_cpeptide_old cpep_ins_old, double bw){
    double curr_i_l = ins_old.I_l + T * ( -(m1+ins_old.m3)*ins_old.I_l + m2*ins_old.I_p + cpep_ins_old.isr/bw );
    return curr_i_l;
}

// A3
double m3(insulin_kinetics_old ins_old){
    double curr_m3 = (ins_old.HE*m1)/(1-ins_old.HE);
    return curr_m3;
}

// A4
double HE(insulin_kinetics_old ins_old, glucose_kinetics_old gluc_old){
    double a0G = Heb+aG*Gb;
    double curr_he = -aG * gluc_old.G + a0G;
    return curr_he;
}