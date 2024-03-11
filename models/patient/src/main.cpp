#include "main.h"

using namespace std;

int main(int argc, char *argv[]) {
    #if (DEBUG > 0)
    setvbuf(stdout, (char*) NULL, _IONBF, 0);
    setvbuf(stderr, (char*) NULL, _IONBF, 0);
    #endif
    redisContext *c2r;
    redisReply *reply;
    unsigned seed;
    int pid = getpid();

    // Initialize patient characteristics
    if(argc != 5){
        fprintf(stderr, "Only four arguments required, more where given:\n\tusage: main sex:bool, age:int, weight:int, height:int");
        return -1;
    }

    struct time time_p = {0};
    
    /*int ciao = 0;
    printf("%d\n",pid);
    while(ciao == 0){
        sleep(5);
    }*/
    // setup input vars
    bool sex = atoi(argv[1]);
    int age = atoi(argv[2]);
    double weight = stod(argv[3]);
    double height = stod(argv[4]);

    // Patient values

    double bmi = weight/(pow(height/100, 2));
    double b1 = log(2) / (0.14*age+29.16);
    double a1;
    double fra;
    if(bmi <= 27){
        a1 = 0.14;
        fra = 0.76;
    }else{
        a1 = 0.152;
        fra = 0.78;
    }
    double bsa = 0.007194 * pow(height,0.725) * pow(weight,0.425);
    double Vc;
    if (sex == 1){
        Vc = 1.92*bsa+0.64;
    }else{
        Vc = 1.11*bsa+2.04;
    }
    double k12 = fra*b1+(1-fra)*a1;
    double k01 = (a1*b1)/k12;
    double k21 = a1+b1-k12-k01;
    
    // Initialize structs for old functions values
    double Gpb = Gb*Vg;
    double Gtb;
    double Vm0;
    if(Gpb <= ke2){
        Gtb = (Fcns-EGPb+k1*Gpb)/k2;
        Vm0 = (EGPb - Fcns)*(km0+Gtb)/Gtb;
    }else{
        Gtb = ( (Fcns-EGPb+ke1*(Gpb-ke2))/Vg+k1*Gpb )/k2;
        Vm0 = ( EGPb-Fcns-ke1*(Gpb-ke2) ) * (km0+Gtb)/Gtb;
    }
    glucose_kinetics_old gluc_kin = {Gpb,Gtb,Gb};

    double Ipb = Ib*Vi; 
    //double HEb = max((SRb-m4*Ipb)/(SRb+m2*Ipb), 0.0);
    double HEb = 0.51;
    double m3_0 = (HEb*m1)/(1-HEb);
    //double Ilb = (Ipb*m2+SRb)/(m1+m3_0);
    double Ilb = 15;
    double Ievb = Ipb*m5/m6;
    insulin_kinetics_old ins_kin = {Ilb,Ipb,Ievb,Ib,m3_0,HEb};

    rate_glucose_app_old rate_gluc = {0,0,0,0,0};

    double kp1 = EGPb+kp2*Gpb+kp3*Ib+kp4*Ilb;
    endog_glucose_prod_old end_gluc = {EGPb, Ib, Ib};

    double U_id_b = (Vm0 * Gtb) / (km0 + Gtb);
    glucose_utilization_old gluc_util = {U_id_b,0};
    
    renal_exrection_old ren_excr = {0};

    double cp2b = Cpb*k21/k12;
    cpeptide_kinetics_old cpep_kin = {Cpb,cp2b};

    double isr_b = Cpb*Vc*k01;
    insulin_cpeptide_old ins_cpep = {isr_b,0,0}; 
    
    // where the output of the insulin pump will be stored
    double u = 0;

    seed = (unsigned) time(NULL);
    srand(seed);
    // redis client connects to server
    printf("main(): pid %d: user patient: connecting to redis ...\n", pid);
    c2r = redisConnect("localhost", 6379);
    printf("main(): pid %d: user patient: connected to redis\n", pid);

    // Delete streams if exists
    reply = RedisCommand(c2r, "DEL %s", PUMP_TO_PATIENT);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    reply = RedisCommand(c2r, "DEL %s", PATIENT_TO_PUMP);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    reply = RedisCommand(c2r, "DEL %s", ENV_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    reply = RedisCommand(c2r, "DEL %s", DUMMY_ENV_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);

    /* Create streams/groups */
    initStreams(c2r, PUMP_TO_PATIENT);
    initStreams(c2r, PATIENT_TO_PUMP);
    initStreams(c2r, ENV_STREAM);
    initStreams(c2r, DUMMY_ENV_STREAM);


    // Create and connect to database
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    init_logdb(db, pid);

    long nseconds = 0;
    char time_str[13];
    time_db(&time_p, time_str);

    log2db(db, pid, nseconds, time_str, gluc_kin.G, ins_kin.I, rate_gluc.q_sto, end_gluc.egp, gluc_util.u_id, ren_excr.e, ins_cpep.isr);
    while (get_time(&time_p) <= MINUTES_PER_DAY){
        long nseconds_diff = get_curr_nsecs() - nseconds;
        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter patient COUNT 1 BLOCK 10000000000 NOACK STREAMS %s >", ENV_STREAM);
        char* delta_str = new char[64];
        ReadStreamMsgVal(reply,0,0,1, delta_str);
        int delta = atoi(delta_str);
        //int delta = 1;

        double egp_new = EGP(kp1, ins_kin, gluc_kin, end_gluc);
        double x_l_new = X_L(end_gluc);
        double I_f_new = I_f(ins_kin, end_gluc);

        double x_new = X(ins_kin, gluc_util);
        double u_id_new = U_id(Gpb,Gtb,Vm0,gluc_kin,gluc_util);

        double e_new = E(gluc_kin, ren_excr);

        double cp_1_new = cp_1(k01,k12,k21,Vc, ins_cpep, cpep_kin);
        double cp_2_new = cp_2(k12,k21,cpep_kin);

        double isr_new = ISR(isr_b, ins_cpep);
        double isr_s_new = ISR_s(Vc, gluc_kin, ins_cpep);
        double isr_d_new = ISR_d(Vc, gluc_kin);

        double I_new = I(u, ins_kin);
        double I_ev_new = I_ev(ins_kin);
        double I_p_new = I_p(u, ins_kin);
        double I_l_new = I_l(weight, ins_kin, ins_cpep);
        double m3_new = m3(ins_kin);
        double HE_new = HE(ins_kin, gluc_kin);

        double G_p_new = G_p(gluc_kin,end_gluc,rate_gluc,gluc_util,ren_excr);
        double G_t_new = G_t(gluc_kin,gluc_util);
        double G_new = G(gluc_kin);

        double Qsto1_new = Q_sto_1(dose, delta,rate_gluc);
        double Qsto2_new = Q_sto_2(dose, rate_gluc);
        double Qsto_new = Q_sto(rate_gluc);
        double Qgut_new = Q_gut(dose, rate_gluc);
        double Ra_meal_new = Ra_meal(weight, rate_gluc);

        if (check_time(&time_p,TEST_TIME,0)){

            reply = RedisCommand(c2r, "XADD %s * %s %.2f", PATIENT_TO_PUMP, "glucose", G_new);
            assertReplyType(c2r, reply, REDIS_REPLY_STRING);
            freeReplyObject(reply);
        }
        if(check_time(&time_p, TEST_TIME, 1)){
            reply = RedisCommand(c2r, "XREADGROUP GROUP diameter patient COUNT 1 BLOCK 10000000000 NOACK STREAMS %s >", PUMP_TO_PATIENT);
            char *comp_dose = new char[64];
            ReadStreamMsgVal(reply,0,0,1, comp_dose);

            u = stod(comp_dose);
            //cout<<"T: "<<t<<" Glucose: "<<G_new<<" Dose received: "<<u<<endl;
            freeReplyObject(reply);
        }
        
        gluc_kin = {G_p_new,G_t_new,G_new};
        ins_kin = {I_l_new,I_p_new,I_ev_new,I_new,m3_new, HE_new};
        rate_gluc = {Qsto_new, Qsto1_new, Qsto2_new, Qgut_new, Ra_meal_new};
        end_gluc = {egp_new,x_l_new,I_f_new};
        gluc_util = {u_id_new, x_new};
        ren_excr = {e_new};
        cpep_kin = {cp_1_new,cp_2_new};
        ins_cpep = {isr_new, isr_s_new, isr_d_new};

        update_time(&time_p);
        time_db(&time_p, time_str);
        log2db(db, pid, nseconds_diff, time_str, gluc_kin.G, ins_kin.I, rate_gluc.q_sto, end_gluc.egp, gluc_util.u_id, ren_excr.e, ins_cpep.isr);
        
        // dummy comms to syncronize environment
        reply = RedisCommand(c2r, "XADD %s * %s %s", DUMMY_ENV_STREAM, "ok", "ok");
        freeReplyObject(reply);

        usleep(1000*T);
    }  // while ()
    
    redisFree(c2r);
}

long get_curr_nsecs(){
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ( (long) (ts.tv_sec * 1000000000L + ts.tv_nsec));
}




