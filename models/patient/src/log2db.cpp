#include "main.h"

/* buy stock  */

void log2db(Con2DB db1, int pid, long int nanosec, int t, double G, double I, double Qsto, double EGP, double Uid, double E, double ISR){

    PGresult *res;
    int rows, k;
    char trcolor[20];
    long int dbnanosec, nsafters;
    char datebuf[1000];
    char sqlcmd[1000];


    #if (DEBUG > 1000000)
    fprintf(stderr, "log2db(): pid = %d, varname = %s\n", pid, "x");
    #endif

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'G\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_G = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'I\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_I = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'Qsto\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_Qsto = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'EGP\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_EGP = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'Uid\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_Uid = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'E\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_E = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'ISR\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_ISR = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    #if (DEBUG > 1000000)
    fprintf(stderr, "log2db(): vid = %d\n", vid);
    #endif


    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

        
    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_G, G, "Glucose value",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_I, I, "Insulin value",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_EGP, EGP, "Endogenous glucose prod",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_Qsto, Qsto, "Glucose in stomach",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_Uid, Uid, "Insulin utilization",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_E, E, "Renal excretion",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_ISR, ISR, "Insulin secretion",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

        
    sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        
    #if (DEBUG > 0)

        // fprintf(stderr, "log2db(): check insertion\n");

    sprintf(sqlcmd, "SELECT * FROM LogTable where (nanosec = %ld)", nanosec);

    res = db1.ExecSQLtuples(sqlcmd);
    rows = PQntuples(res);

    dbnanosec = strtol(PQgetvalue(res, 0, PQfnumber(res, "nanosec")), NULL, 10);

    fprintf(stderr, "log2db(): inserted in LogTable (%ld, %d, %d, \'%s\')\n",
        dbnanosec,
        atoi(PQgetvalue(res, 0, PQfnumber(res, "vid"))),
        atoi(PQgetvalue(res, 0, PQfnumber(res, "varvalue"))),
        PQgetvalue(res, 0, PQfnumber(res, "loginfo"))
        );
    PQclear(res);

    nsafters = nanos2day(datebuf, dbnanosec);

    fprintf(stderr, "log2db(): ns = %ld = TIME_UTC = %s + %ld ns\n", dbnanosec, datebuf, nsafters);
    #endif




        
}  /*   log2db()  */
 
