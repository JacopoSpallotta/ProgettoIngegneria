#include "main.h"
#include "patient.h"
#include "insulin_kinetics.cpp"
#include "glucose_kinetics.cpp"

using namespace std;

double U_ii(glucose_utilization_old old, int t){
    double curr_u_ii = old.u_ii + T * Fcns;
    old.u_ii = curr_u_ii;
    return curr_u_ii;
}

double U_id(glucose_utilization_old old, int t){
    double Gpb = Gb*Vg;
    double Gtb = (Fcns - EGPb + k1*Gpb) / (double) k2;
    double Vm0 = (EGPb-Fcns)*(km0+Gtb)/ Gtb;
    double curr_u_id = old.u_id + T * ( ( ( Vm0 + Vmx * X(old, t) * (1+r1*risk(G(t))) ) * G_t(t) ) / (km0 + G_t(t)) );
    old.u_id = curr_u_id;
    return curr_u_id;
}

double X(glucose_utilization_old old, int t){
    double curr_x = old.x + T * (-p2U * old.x + p2U * (I(t)-Ib));
    old.x = curr_x;
    return curr_x;
}

double risk(double G){
    if (G >= Gb){
        return 0;
    }else if(G >= G_th && G <= Gb){
        return 10*pow(f(G), 2);
    }else if(G <= G_th){
        return 10* pow(f(G_th),2);
    }
}

double f(double G){
    return pow(log(G),r2) - pow(log(Gb), r2);
}

