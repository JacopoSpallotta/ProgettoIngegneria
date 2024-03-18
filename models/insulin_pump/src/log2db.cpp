#include "log2db.h"

/* buy stock  */

void log2db(Con2DB db1, int pid, long int nanosec, char* t, insulin_pump_state pump_state, double comp_dose){

    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'pump_state\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_state = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);
    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'comp_dose\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid_comp_dose = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);
    char pump_state_str[30];

    switch (pump_state)
    {
    case 0:
        sprintf(pump_state_str, "idle");
        break;
    case 1:
        sprintf(pump_state_str, "test");
        break;
    case 2:
        sprintf(pump_state_str, "compute_release");
        break;
    }



    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

        
    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %d, \'%s\', interval (3) \'%s\') ON CONFLICT DO NOTHING", nanosec, vid_state, pump_state, pump_state_str,t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);


    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %f, \'%s\', interval (3) \'%s\') ON CONFLICT DO NOTHING", nanosec, vid_comp_dose, comp_dose, "Computed dose",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

        
    sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        
    #if (DEBUG > 0)
    int rows;
    long int dbnanosec;
    // fprintf(stderr, "log2db(): check insertion\n");

    sprintf(sqlcmd, "SELECT * FROM LogTable where (nanosec = %ld)", nanosec);

    res = db1.ExecSQLtuples(sqlcmd);
    rows = PQntuples(res);

    dbnanosec = strtol(PQgetvalue(res, 0, PQfnumber(res, "nanosec")), NULL, 10);

    for(int i = 0; i < rows; i++){
        fprintf(stderr, "log2db(): inserted in LogTable (%ld, %d, %d, \'%s\',%d)\n",
            dbnanosec,
            atoi(PQgetvalue(res, i, PQfnumber(res, "vid"))),
            atoi(PQgetvalue(res, i, PQfnumber(res, "varvalue"))),
            PQgetvalue(res, i, PQfnumber(res, "loginfo")),
            atoi(PQgetvalue(res, i, PQfnumber(res, "t")))
        );
    }
    PQclear(res);

    #endif
        
}  /*   log2db()  */
 
