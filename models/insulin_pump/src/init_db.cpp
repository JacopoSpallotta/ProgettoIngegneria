#include "init_db.h"

/* buy stock  */

void init_logdb(Con2DB db1, int pid) {

  PGresult *res;
  int rows, k;
  
  char sqlcmd[1000];

/*  init  */  

  sprintf(sqlcmd, "BEGIN"); 
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

  // Logging state of pump
  sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
              pid, "Insulin pump", "pump_state", "discrete", "State of insulin pump");

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);


  // Logging comp_dose
  sprintf(sqlcmd, "INSERT INTO Timevar VALUES (DEFAULT, %d, \'%s\', \'%s\', \'%s\', \'%s\') ON CONFLICT DO NOTHING",
            pid, "Insulin pump", "comp_dose", "double", "dose (pmol/L)");

  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);


  
  sprintf(sqlcmd, "COMMIT"); 
  res = db1.ExecSQLcmd(sqlcmd);
  PQclear(res);

      
#if (DEBUG > 0)
    sprintf(sqlcmd, "SELECT * FROM Timevar where ((pid = %d) AND ( (varname = 'pump_state') OR (varname = 'comp_dose')) )", pid);

    res = db1.ExecSQLtuples(sqlcmd);
    rows = PQntuples(res);

    for(int i = 0; i < 2; i++){ 
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
 
