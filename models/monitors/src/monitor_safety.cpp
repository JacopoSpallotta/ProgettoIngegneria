#include "monitor.h"

void monitor_safety(Con2DB* db, struct m_safety* m_safety, double gluc_val){
    PGresult* res;
    char sqlcmd[1000];

    (m_safety -> tuples_read)++;

    update_time(&(m_safety -> time_p));
    char time_str[13];
    time_db( &(m_safety -> time_p), time_str);

    if(gluc_val < 50){
        sprintf(sqlcmd, "INSERT INTO SafetyTable(t,safety) VALUES (interval (3) \'%s\',%s) ON CONFLICT DO NOTHING", time_str ,"TRUE");
    }else{
        sprintf(sqlcmd, "INSERT INTO SafetyTable(t,safety) VALUES (interval (3) \'%s\',%s) ON CONFLICT DO NOTHING", time_str ,"FALSE");
    }

    res = (*db).ExecSQLcmd(sqlcmd);
    PQclear(res);
        
}