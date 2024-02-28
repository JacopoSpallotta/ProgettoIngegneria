#include "monitor.h"

void monitor_minimalDose(Con2DB* db, struct m_minDose* m_minDose){
    PGresult* res;
    double daily_doses = 0;
    char sqlcmd[1000];

    sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'comp_dose' ");

    res = (*db).ExecSQLtuples(sqlcmd);
    int rows = PQntuples(res); // num of rows in database
    if (rows > m_minDose -> tuples_read){ // if num rows grew in past cycle, read
        daily_doses = stod(PQgetvalue(res, rows-1, PQfnumber(res, "varvalue")));
        PQclear(res);
        m_minDose -> tuples_read++;
        if ((m_minDose -> tuples_read % 1440) == 0){ // writes once a day
            sprintf(sqlcmd, "INSERT INTO MonitorTable(minDose) VALUES (%d) ON CONFLICT DO NOTHING", daily_doses);
        }

        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
}