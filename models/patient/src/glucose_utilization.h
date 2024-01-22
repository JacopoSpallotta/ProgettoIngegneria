#ifndef glucose_utilization
#define glucose_utilization

#include "patient.h"
#include <cmath>

using namespace std;

double U_ii();
double X(insulin_kinetics_old ins_old, glucose_utilization_old util_old);
double f(double G);
double risk(double G);
double U_id(double Gpb, double Gtb, double Vm0, glucose_kinetics_old kin_old, glucose_utilization_old util_old);

#endif