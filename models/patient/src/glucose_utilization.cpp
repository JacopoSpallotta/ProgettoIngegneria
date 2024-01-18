#include "main.h"
#include "patient.h"
#include "insulin_kinetics.cpp"
#include "glucose_kinetics.cpp"

using namespace std;

// A12
double U_ii(glucose_utilization_old old){
    return Fcns;
}

// A13
double U_id(glucose_kinetics_old kin_old, glucose_utilization_old util_old){
    double Gpb = Gb*Vg;
    double Gtb = (Fcns - EGPb + k1*Gpb) / (double) k2;
    double Vm0 = (EGPb-Fcns)*(km0+Gtb)/ Gtb;

    double curr_u_id = util_old.u_id + T * ( ( ( Vm0 + Vmx * util_old.x * (1+r1*risk(kin_old.G)) ) * kin_old.G_t ) / (km0 + kin_old.G_t) );
    return curr_u_id;
}

// A14
double X(insulin_kinetics_old ins_old, glucose_utilization_old util_old){
    double curr_x = util_old.x + T * (-p2U * util_old.x + p2U * (ins_old.I - Ib));
    return curr_x;
}

// A15
double risk(double G){
    if (G >= Gb){
        return 0;
    }else if(G >= G_th && G <= Gb){
        return 10*pow(f(G), 2);
    }else if(G <= G_th){
        return 10* pow(f(G_th),2);
    }
}

// A16
double f(double G){
    return pow(log(G),r2) - pow(log(Gb), r2);
}

