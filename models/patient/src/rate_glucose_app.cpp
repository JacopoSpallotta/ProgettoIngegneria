#include "rate_glucose_app.h"

// A7
double Alpha (double dose){
    double alpha = ((double) 5) / (2 * dose * (1-b));
    return alpha;
}

// A8
double Beta (double dose){
    double beta = ((double) 5) / (2*dose*d);
    return beta;
}

// A6
double K_empt(double q_sto, double dose) {
    double k_empt = kmin + ((kmax - kmin) / (double)2) * (tanh(Alpha(dose)*(q_sto - Beta(dose)*dose )) - tanh(Beta(dose)*(q_sto - d*dose)) + 2 );
    return k_empt;
}

// A5
double Q_sto(rate_glucose_app_old g_app_old) {
    double curr_q_sto = (g_app_old.q_sto_1 + g_app_old.q_sto_2);
    return curr_q_sto;
}

// A5

double Q_sto_1(double dose, int delta, rate_glucose_app_old g_app_old) {
    double curr_q_sto_1 = g_app_old.q_sto_1 + T * ((-kmax * g_app_old.q_sto_1) + dose * delta);
    return curr_q_sto_1;
}

// A5
double Q_sto_2(double dose, rate_glucose_app_old g_app_old) {
    double curr_q_sto_2 = g_app_old.q_sto_2 + T * ( (-K_empt(g_app_old.q_sto, dose) * g_app_old.q_sto_2)+(kmax * g_app_old.q_sto_1));
    return curr_q_sto_2;
}

// A5
double Q_gut(double dose, rate_glucose_app_old g_app_old) {
    double curr_q_gut = g_app_old.q_gut + T * ((-kabs * g_app_old.q_gut) + K_empt(g_app_old.q_sto, dose)*g_app_old.q_sto_2);
    return curr_q_gut;
}

// A5
double Ra_meal (double bw, rate_glucose_app_old g_app_old) {
    double ra_meal = (F*kabs*g_app_old.q_gut)/bw;
    return ra_meal;
}

