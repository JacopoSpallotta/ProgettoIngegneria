#include "main.h"

/* buy stock  */

void init_logdb(Con2DB db1, int pid) {

    PGresult *res;
    int rows, k;
    char sqlcmd[1000];
 
 
 /*  init  */
 
    sprintf(sqlcmd, "BEGIN"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Saving G(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
                pid, "Patient", "G", "double", "Plasma glucose concentration");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging I(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "I", "double", "Plasma insulin concentration");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging Qsto(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "Qsto", "double", "Amount of glucose in the stomach");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging EGP(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "EGP", "double", "endogenous glucose production");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);
    
    // Logging Uid(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "Uid", "double", "Insulin-dependent utilization");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging E(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "E", "double", "Renal excretion");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    // Logging ISR(t)
    sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
	            pid, "Patient", "ISR", "double", "Insulin and c-peptide secretion");

    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

    sprintf(sqlcmd, "COMMIT"); 
    res = db1.ExecSQLcmd(sqlcmd);
    PQclear(res);

      
#if (DEBUG > 0)
      sprintf(sqlcmd, "SELECT * FROM Timevar where ((pid = %d) AND (varname = 'x'))", pid);

    res = db1.ExecSQLtuples(sqlcmd);
    rows = PQntuples(res);
      
    fprintf(stderr, "initdb(): inserted in Timevar (%d, %d, %s, %s, %s, %s)\n",
	    atoi(PQgetvalue(res, 0, PQfnumber(res, "vid"))),
	    atoi(PQgetvalue(res, 0, PQfnumber(res, "pid"))),
	    PQgetvalue(res, 0, PQfnumber(res, "sysname")),
	    PQgetvalue(res, 0, PQfnumber(res, "varname")),
	    PQgetvalue(res, 0, PQfnumber(res, "vardomain")),
	    PQgetvalue(res, 0, PQfnumber(res, "varinfo"))
	    );
#endif


     
 }  /*   init_logdb()  */
 
