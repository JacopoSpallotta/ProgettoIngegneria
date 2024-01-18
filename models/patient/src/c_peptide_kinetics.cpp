#include "main.h"
#include "patient.h"

using namespace std;

// A18
double cp_1(insulin_cpeptide_old cpep_ins_old, cpeptide_kinetics_old cpep_kin_old){
    double curr_cp_1 = cpep_kin_old.cp_1 + T * (-(k_01+k_21) * cpep_kin_old.cp_1 + k_12*cpep_kin_old.cp_2 + cpep_ins_old.isr/Vc);
    return curr_cp_1;
}

// A18
double cp_2(cpeptide_kinetics_old cpep_kin_old){
    double curr_cp_2 = cpep_kin_old.cp_2 + T * (-k_12*cpep_kin_old.cp_2 + k_21*cpep_kin_old.cp_1);
    return curr_cp_2;
}