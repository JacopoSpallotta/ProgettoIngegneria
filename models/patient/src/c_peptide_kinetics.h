#ifndef c_peptide_kinetics
#define c_peptide_kinetics

#include "patient.h"

using namespace std;

double cp_1(double k_01, double k_12, double k_21, double Vc, insulin_cpeptide_old cpep_ins_old, cpeptide_kinetics_old cpep_kin_old);
double cp_2(double k_12, double k_21, cpeptide_kinetics_old cpep_kin_old);

#endif