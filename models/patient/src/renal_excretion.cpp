#include "renal_excretion.h"

// A17
double E(glucose_kinetics_old kin_old, renal_exrection_old ren_old){
    double e_t = 0;
    if (kin_old.G_p > ke2){
        e_t = ke1 * (kin_old.G_p - ke2);
    }
    double curr_e = ren_old.e + T * e_t;
    return curr_e;
}

