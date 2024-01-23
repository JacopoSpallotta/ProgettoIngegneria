#include "glucose_kinetics.h"

double G(glucose_kinetics_old g_old){
    double curr_g = g_old.G_p / Vg;
    return curr_g;
}

double G_t(glucose_kinetics_old g_old, glucose_utilization_old util_old) {
    double curr_g_t = g_old.G_t + T * (- util_old.u_id + k1 * g_old.G_p - k2 * g_old.G_t);
    return curr_g_t;
}

double G_p(glucose_kinetics_old g_old, endog_glucose_prod_old end_old, rate_glucose_app_old rate_old, glucose_utilization_old util_old, renal_exrection_old ren_old) {
    double curr_g_p = g_old.G_p + T * (end_old.egp + rate_old.ra_meal - Fcns - ren_old.e - k1 * g_old.G_p + k2 * g_old.G_t);
    return curr_g_p;
}