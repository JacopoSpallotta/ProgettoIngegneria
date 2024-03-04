#include "log2db.h"

/* buy stock  */

void log2db(Con2DB db1, int pid, long int nanosec, char* t, int delta){

    PGresult *res;
    char sqlcmd[1000];

    sprintf(sqlcmd, "SELECT vid FROM TimeVar where ((pid = %d) AND (varname = \'delta\'))", pid);
    res = db1.ExecSQLtuples(sqlcmd);
    int vid = atoi(PQgetvalue(res, 0, PQfnumber(res, "vid")));
    PQclear(res);

    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

        
    sprintf(sqlcmd, "INSERT INTO LogTable VALUES (%ld, %d, %d, \'%s\', time (3) \'%s\') ON CONFLICT DO NOTHING", nanosec, vid, delta, "Food intake",t);

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

        
    sprintf(sqlcmd, "COMMIT"); 
        res = db1.ExecSQLcmd(sqlcmd);
        PQclear(res);

        
    #if (DEBUG > 0)

        // fprintf(stderr, "log2db(): check insertion\n");
    int rows;
    long int dbnanosec;
    
    sprintf(sqlcmd, "SELECT * FROM LogTable where (nanosec = %ld)", nanosec);

    res = db1.ExecSQLtuples(sqlcmd);
    rows = PQntuples(res);

    dbnanosec = strtol(PQgetvalue(res, 0, PQfnumber(res, "nanosec")), NULL, 10);

    fprintf(stderr, "log2db(): inserted in LogTable (%ld, %d, %d, \'%s\', %d)\n",
        dbnanosec,
        atoi(PQgetvalue(res, 0, PQfnumber(res, "vid"))),
        atoi(PQgetvalue(res, 0, PQfnumber(res, "varvalue"))),
        PQgetvalue(res, 0, PQfnumber(res, "loginfo")),
        atoi(PQgetvalue(res, 0, PQfnumber(res, "t")))
        );
    PQclear(res);

    #endif




        
}  /*   log2db()  */
 
