#include "main.h"
#include "patient.h"
#include "glucose_kinetics.cpp"

using namespace std;

// A19
double ISR(insulin_cpeptide_old cpep_ins_old){
    double curr_isr = cpep_ins_old.isr + T * ( cpep_ins_old.isr_s + cpep_ins_old.isr_d + cpep_ins_old.isr_b );
    return curr_isr;
}

// A20
double ISR_s(glucose_kinetics_old gluc_old, insulin_cpeptide_old cpep_ins_old){
    double curr_isr_s = cpep_ins_old.isr_s + T * ( -alpha_a20 * ( cpep_ins_old.isr_s - Vc*PHIs*( gluc_old.G - h) ) );
    return curr_isr_s;
}

// A21
double ISR_d(glucose_kinetics_old gluc_old){
    double dG = (G(gluc_old) - gluc_old.G) / T; // TODO vedere ordine esecuzione G e ISR
    double curr_isr_d = 0;
    if(dG >= 0){
        curr_isr_d = Vc * PHId * dG;
    }
    return curr_isr_d;
}

// A22
double ISR_b(){
    return Cpb*k_01*Vc;
}