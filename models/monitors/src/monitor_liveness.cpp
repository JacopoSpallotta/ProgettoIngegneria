#include "monitor.h"

void monitor_liveness(Con2DB* db, struct m_liveness* m_liveness){
    PGresult* res;
    double gluc_val = 0;
    char sqlcmd[1000];

    sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'G' ");

    res = (*db).ExecSQLtuples(sqlcmd);
    int rows = PQntuples(res);

    if(rows > m_liveness -> tuples_read){
        gluc_val = stod(PQgetvalue(res, rows-1, PQfnumber(res, "varvalue")));
        PQclear(res);
        m_liveness -> gluc_sum += gluc_val;
        m_liveness -> tuples_read++; 
        update_time(&(m_liveness -> time_p));

        if( check_time ( &(m_liveness -> time_p), 60, 0)){
            double mean_gluc = m_liveness -> gluc_sum / 60.0;
            m_liveness -> gluc_sum = 0;
            char time_str[13];
            time_db( &(m_liveness -> time_p), time_str);
            if(mean_gluc >= 110 && mean_gluc <= 90){
                sprintf(sqlcmd, "INSERT INTO LivenessTable(t, liveness) VALUES (interval (3) \'%s\',%s) ON CONFLICT DO NOTHING", time_str, "TRUE");
            }else{
                sprintf(sqlcmd, "INSERT INTO LivenessTable(t, liveness) VALUES (interval (3) \'%s\',%s) ON CONFLICT DO NOTHING", time_str, "FALSE");
            }

            res = (*db).ExecSQLcmd(sqlcmd);
            PQclear(res);
        }
    }
    
}