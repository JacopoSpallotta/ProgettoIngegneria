#include "c_peptide_kinetics.h"

// A18
double cp_1(double k_01, double k_12, double k_21, double Vc, insulin_cpeptide_old cpep_ins_old, cpeptide_kinetics_old cpep_kin_old){
    double curr_cp_1 = cpep_kin_old.cp_1 + T * (-(k_01+k_21) * cpep_kin_old.cp_1 + k_12*cpep_kin_old.cp_2 + cpep_ins_old.isr/Vc);
    return curr_cp_1;
}

// A18
double cp_2(double k_12, double k_21, cpeptide_kinetics_old cpep_kin_old){
    double curr_cp_2 = cpep_kin_old.cp_2 + T * (-k_12*cpep_kin_old.cp_2 + k_21*cpep_kin_old.cp_1);
    return curr_cp_2;
}