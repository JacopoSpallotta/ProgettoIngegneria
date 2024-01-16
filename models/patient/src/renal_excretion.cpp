#include "main.h"
#include "patient.h"
#include "glucose_kinetics.cpp"

using namespace std;

double E(renal_exrection_old old, int t){
    double e_t = 0;
    if (G_p(t) > ke2){
        e_t = ke1 * (G_p(t) - ke2);
    }
    double curr_e = old.e + T * e_t;
    old.e = curr_e;
    return curr_e;
}