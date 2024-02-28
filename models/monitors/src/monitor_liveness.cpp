#include <monitor.h>

void monitor_liveness(Con2DB* db, struct m_liveness* m_liveness){
    PGresult* res;
    double gluc_val = 0;
    char sqlcmd[1000];

    sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'G' ");

    res = (*db).ExecSQLtuples(sqlcmd);
    int rows = PQntuples(res);
    bool tuple_read = false;
    if(rows > m_liveness -> tuples_read){
        gluc_val = stod(PQgetvalue(res, rows-1, PQfnumber(res, "varvalue")));
        PQclear(res);
        m_liveness -> gluc_sum += gluc_val;
        m_liveness -> tuples_read++; 
        tuple_read = true;
    }
    if( tuple_read && (m_liveness -> tuples_read % 60) == 0){
        double mean_gluc = m_liveness -> gluc_sum / 60.0;
        m_liveness -> gluc_sum = 0;
        cout << mean_gluc<< endl;

        sprintf(sqlcmd, "BEGIN"); 
        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);

        if(mean_gluc >= 120){
            sprintf(sqlcmd, "INSERT INTO MonitorTable(liveness) VALUES (%s) ON CONFLICT DO NOTHING", "TRUE");
        }else{
            sprintf(sqlcmd, "INSERT INTO MonitorTable(liveness) VALUES (%s) ON CONFLICT DO NOTHING", "FALSE");
        }

        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);

        sprintf(sqlcmd, "COMMIT"); 
        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
}