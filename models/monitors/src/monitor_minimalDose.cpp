#include "monitor.h"

void monitor_minimalDose(Con2DB* db, struct m_minDose* m_minDose){
    PGresult* res;
    char sqlcmd[1000];
    int comp_dose = 0;

    sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'comp_dose' ");

    res = (*db).ExecSQLtuples(sqlcmd);
    int rows = PQntuples(res); // num of rows in database
    
    if (rows > m_minDose -> tuples_read){ // if num rows grew in past cycle, read
        comp_dose = stod(PQgetvalue(res, rows-1, PQfnumber(res, "varvalue")));
        PQclear(res);

        m_minDose -> daily_dose += comp_dose;
        m_minDose -> tuples_read++;

        cout <<comp_dose<<endl;
        if ((m_minDose -> tuples_read % 1440) == 0){ // writes once a day
            sprintf(sqlcmd, "INSERT INTO MinimalDose(t, min_dose) VALUES (%d, %d) ON CONFLICT DO NOTHING", m_minDose -> tuples_read, m_minDose -> daily_dose);
            cout <<m_minDose->daily_dose<<endl;

            m_minDose -> daily_dose = 0;
            res = (*db).ExecSQLcmd(sqlcmd);
            PQclear(res);
        }
    }
}