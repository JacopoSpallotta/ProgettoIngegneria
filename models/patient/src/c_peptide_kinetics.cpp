#include "main.h"
#include "patient.h"

using namespace std;

double cp_1(c_peptide_kinetics_old old, int t){
    double curr_cp_1 = -(k_01+k_21) * old.cp_1 + k_12*cp_2(old, t);
}

double cp_2(c_peptide_kinetics_old old, int t){
    return 0.0;
}