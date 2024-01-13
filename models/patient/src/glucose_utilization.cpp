#include "main.h"
#include "patient.h"
#include "insulin_kinetics.cpp"
#include "glucose_kinetics.cpp"

using namespace std;

double U_ii(int t){
    return 0.0; // Fcns = 1
}

double U_id(int x, int t){
    double num = (Vm0() + Vmx)
}

double X(double x_old, int t){
    return (-p2U * x_old + p2U * (I(t)-Ib));
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

