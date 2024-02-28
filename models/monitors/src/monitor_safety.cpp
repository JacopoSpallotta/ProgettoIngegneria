#include <monitor.h>

void monitor_safety(Con2DB* db, struct m_safety* m_safety){
    PGresult* res;
    double gluc_val = 0;
    char sqlcmd[1000];
    
    sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'G' ");

    res = (*db).ExecSQLtuples(sqlcmd);
    int rows = PQntuples(res);
    if(rows > m_safety -> tuples_read){
        gluc_val = stod(PQgetvalue(res, rows-1, PQfnumber(res, "varvalue")));
        PQclear(res);
        (m_safety -> tuples_read)++;

        sprintf(sqlcmd, "BEGIN"); 
        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);

        if(gluc_val < 50){
            sprintf(sqlcmd, "INSERT INTO MonitorTable(safety) VALUES (%s) ON CONFLICT DO NOTHING", "TRUE");
        }else{
            sprintf(sqlcmd, "INSERT INTO MonitorTable(safety) VALUES (%s) ON CONFLICT DO NOTHING", "FALSE");
        }

        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);

        
    }
}