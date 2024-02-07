#include "init_db.h"

void init_logdb(Con2DB db1, int pid) {

    PGresult *res;
    int rows, k;
    char sqlcmd[1000];

 
 /*  init  */
    
    // Delete tables from prevoius runs, this process HAS TO start FIRST
    sprintf(sqlcmd, "TRUNCATE LogTable,TimeVar RESTART IDENTITY;"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
 
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Saving G(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
                pid, "Patient", "G", "double", "Plasma glucose concentration (mg/dL)");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging I(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "I", "double", "Plasma insulin concentration (pmol/L)");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging Qsto(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "Qsto", "double", "Amount of glucose in the stomach (mg)");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging EGP(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "EGP", "double", "endogenous glucose production");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    
    // Logging Uid(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "Uid", "double", "Insulin-dependent utilization (mg/kg/min)");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging E(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "E", "double", "Renal excretion (mg/kg/min)");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging ISR(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "ISR", "double", "Insulin and c-peptide secretion (pmol/min)");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

      
#if (DEBUG > 0)
    sprintf(sqlcmd, "SELECT * FROM Timevar where ((pid = %d) AND ( (varname = 'G') OR (varname='I') OR (varname='Qsto') OR (varname='EGP') OR (varname='Uid') OR (varname='E') OR (varname='ISR') ));", pid);

    res = db1.ExecSQLtuples(sqlcmd);
    rows = PQntuples(res);
      
    for(int i = 0; i < 7; i++){ 
      fprintf(stderr, "initdb(): inserted in Timevar (%d, %d, %s, %s, %s, %s)\n",
        atoi(PQgetvalue(res, i, PQfnumber(res, "vid"))),
        atoi(PQgetvalue(res, i, PQfnumber(res, "pid"))),
        PQgetvalue(res, i, PQfnumber(res, "sysname")),
        PQgetvalue(res, i, PQfnumber(res, "varname")),
        PQgetvalue(res, i, PQfnumber(res, "vardomain")),
        PQgetvalue(res, i, PQfnumber(res, "varinfo"))
        );
    }
#endif


     
 }  /*   init_logdb()  */
 
