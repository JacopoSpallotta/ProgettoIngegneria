#ifndef patient_h
#define patient_h

const double EGPb = 1.59;
const double kp2 = 0.0008;
const double kp3 = 0.006;
const double kp4 = 0.0484;
const double ke1 = 0.0005;
const double ke2 = 339;
const double Ib = 54;
const double kabs = 0.0542;
const double kmax = 0.0426;
const double kmin = 0.0076;
const double b = 0.7328;
const double d = 0.1014;
const double ki = 0.0075;
const double Vg = 1;
const double Vmx = 0.034; 
const double km0 = 466.2; 
const double k2 = 0.043;
const double k1 = 0.066;
const double p2U = 0.058; 
const double alpha_a20 = 0.034;
const double PHId = 0.000000286;
const double PHIs = 0.0000000203; 
const double Vi = 0.041;
const double aG = 0.005;
const double m4 = 0.443;
const double m5 = 0.26;
const double m6 = 0.017; 
const double m2 = 0.268;
const double m1 = 0.314;
const double Gb = 127;
const double G_th = 50;
const double h = 98.7;
const double Heb = 0.51; 
const double SRb = 737.5;
const double r1 = 0.7419;
const double r2 = 0.0807;
const double Fcns = 7;
const double Cpb = 200;
const double F = 0.9;

const double dose = 105;

struct glucose_kinetics_old{
    double G_p;
    double G_t;
    double G;
};

struct insulin_kinetics_old{
    double I_l;
    double I_p;
    double I_ev;
    double I;
    double m3;
    double HE;
};

struct rate_glucose_app_old{
    double q_sto;
    double q_sto_1;
    double q_sto_2;
    double q_gut;
    double ra_meal;
};

struct endog_glucose_prod_old {
    double egp;
    double x_l;
    double i_f;
};

struct glucose_utilization_old{
    double u_id;
    double x;
};

struct renal_exrection_old{
    double e;
};

struct cpeptide_kinetics_old{
    double cp_1;
    double cp_2;
};

struct insulin_cpeptide_old{
    double isr;
    double isr_s;
    double isr_d;
};

using namespace std;

#endif