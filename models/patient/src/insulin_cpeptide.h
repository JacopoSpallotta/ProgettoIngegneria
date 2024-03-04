#ifndef insulin_cpeptide
#define insulin_cpeptide

#include "patient.h"
#include "main.h"

using namespace std;

double ISR(double isr_b, insulin_cpeptide_old cpep_ins_old);
double ISR_s(double Vc, glucose_kinetics_old gluc_old, insulin_cpeptide_old cpep_ins_old);
double ISR_d(double Vc, glucose_kinetics_old gluc_old);

#endif