#include "main.h"
#include "patient.h"

using namespace std;

// A5
double Q_sto(rate_glucose_app_old g_app_old) {
    double curr_q_sto = g_app_old.q_sto + T * (g_app_old.q_sto_1 + g_app_old.q_sto_2);
    return curr_q_sto;
}

// A5

double Q_sto_1(rate_glucose_app_old g_app_old, double dose) {
    double curr_q_sto_1 = g_app_old.q_sto_1 + T * ((-kmax * g_app_old.q_sto_1) + dose * (rand()%2));
    return curr_q_sto_1;
}

// A5
double Q_sto_2(rate_glucose_app_old g_app_old, double dose) {
    double curr_q_sto_2 = g_app_old.q_sto_2 + T * ( (-K_empt(g_app_old.q_sto, dose) * g_app_old.q_sto_2)+(kmax * g_app_old.q_sto_1));
    return curr_q_sto_2;
}

// A5
double Q_gut(rate_glucose_app_old g_app_old, double dose) {
    double curr_q_gut = g_app_old.q_gut + T * ((-kabs * g_app_old.q_gut) + K_empt(g_app_old.q_sto, dose)*g_app_old.q_sto_2);
    return curr_q_gut;
}

// A5
double Ra_meal (rate_glucose_app_old g_app_old, double bw) {
    double ra_meal = g_app_old.ra_meal + T * ((F*kabs*g_app_old.q_gut)/bw);
    return ra_meal;
}


// A6
double K_empt(double q_sto, double dose) {
    double k_empt = kmin + ((kmax - kmin) / (double)2) * (tanh(Alpha(dose)*(q_sto - Beta(dose)*dose )) - tanh(Beta(dose)*(q_sto - d*dose)) + 2 );
    return k_empt;
}


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