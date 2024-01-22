#ifndef insulin_kinetics
#define insulin_kinetics

#include "patient.h"

using namespace std;

double I(insulin_kinetics_old ins_old, double u);
double I_ev(insulin_kinetics_old ins_old);
double I_p(insulin_kinetics_old ins_old, double u);
double I_l(insulin_kinetics_old ins_old, insulin_cpeptide_old cpep_ins_old, double bw);
double m3(insulin_kinetics_old ins_old);
double HE(insulin_kinetics_old ins_old, glucose_kinetics_old gluc_old);

#endif