#ifndef patient_h
#define pateint_h

#define EGPb 1.59
#define kp2 0.0008
#define kp3 0.006
#define kp4 0.0484
#define ke1 0.0005
#define ke2 339
#define Ib 54
#define kabs 0.0542 
#define kmax 0.0426
#define kmin 0.0076 
#define b	0.7328
#define d	0.1014
#define ki	0.0075
#define Vg	1
#define Vmx	0.034 
#define km0	466.2 
#define k2	0.043 
#define k1	0.066 
#define p2U	0.058 
#define alpha_a20 0.034 
#define PHId 286 
#define PHIs 20.3 
#define Vi	0.041 
#define aG	0.005 
#define m4	0.443 
#define m5	0.26 
#define m6	0.017 
#define m2  0.268
#define m1	0.314 
#define Gb	127 
#define G_th 50
#define SRb	737.5 
#define h	98.7
#define Heb	0.51 
#define r1	0.7419
#define r2	0.0807
#define Fcns 1
#define Cpb 200
#define F 0.9

#define T 0.1

#endif

typedef struct Patient{
    bool sex;
    int age;
    double weight;
    double height;
    double bmi;
    double bsa;
    double b1;
    double a1;
    double fra;
    double vc;
};

typedef struct glucose_kinetics_old{
    double G_p;
    double G_t;
    double G;
};

typedef struct insulin_kinetics_old{
    double I_l;
    double I_p;
    double I_ev;
    double I;
    double m3;
    double HE;
};

typedef struct rate_glucose_app_old{
    double q_sto;
    double q_sto_1;
    double q_sto_2;
    double q_gut;
    double ra_meal;
};

typedef struct endog_glucose_prod_old {
    double egp;
    double x_l;
    double i_f;
};

typedef struct glucose_utilization_old{
    double u_id;
    double x;
};

typedef struct renal_exrection_old{
    double e;
};

typedef struct cpeptide_kinetics_old{
    double cp_1;
    double cp_2;
};

typedef struct insulin_cpeptide_old{
    double isr;
    double isr_s;
    double isr_d;
};

using namespace std;