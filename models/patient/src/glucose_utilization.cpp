#include "glucose_utilization.h"

// A12
double U_ii(){
    return Fcns;
}

// A14
double X(insulin_kinetics_old ins_old, glucose_utilization_old util_old){
    double curr_x = util_old.x + T * (-p2U * util_old.x + p2U * (ins_old.I - Ib));
    return curr_x;
}

// A16
double f(double G){
    return pow(log(G),r2) - pow(log(Gb), r2);
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
    return 0.0;
}

// A13
double U_id(double Gpb, double Gtb, double Vm0, glucose_kinetics_old kin_old, glucose_utilization_old util_old){
    double curr_u_id = ( ( Vm0 + Vmx * util_old.x * (1+r1*risk(kin_old.G)) ) * kin_old.G_t ) / (km0 + kin_old.G_t);
    return curr_u_id;
}

