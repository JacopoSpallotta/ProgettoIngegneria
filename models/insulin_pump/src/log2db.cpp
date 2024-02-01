#include "main.h"

/* buy stock  */

void log2db(Con2DB db1, int pid, long int nanosec, int t, insulin_pump_state pump_state, double comp_dose){

    PGresult *res;
    int rows, k;
    long int dbnanosec, nsafters;
    char datebuf[1000];
    char sqlcmd[1000];



    #if (DEBUG > 1000000)
    fprintf(stderr, "log2db(): pid = %d, varname = %s\n", pid, "x");
    #endif

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'pump_state\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_state = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'comp_dose\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_comp_dose = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);


    #if (DEBUG > 1000000)
    fprintf(stderr, "log2db(): vid = %d\n", vid);
    #endif

    char pump_state_str[30];

    switch (pump_state)
    {
    case 0:
        sprintf(pump_state_str, "test");
        break;
    case 1:
        sprintf(pump_state_str, "idle");
        break;
    case 2:
        sprintf(pump_state_str, "execution");
        break;
    }

    //TODO: Add alert state 


    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

        
    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %d, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_state, pump_state, pump_state_str,t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', %d) ON CONFLICT DO NOTHING", nanosec, vid_comp_dose, comp_dose, "Computed dose",t);

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
 
