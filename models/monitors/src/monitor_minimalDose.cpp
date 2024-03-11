#include "monitor.h"

void monitor_minimalDose(Con2DB* db, struct m_minDose* m_minDose, int comp_dose){
    PGresult* res;
    char sqlcmd[1000];
    
    m_minDose -> daily_dose += comp_dose;
    m_minDose -> tuples_read++;
    update_time(&(m_minDose -> time_p));

    if (check_time(&(m_minDose -> time_p), MINUTES_PER_DAY, 0)){ // writes once a day
        char time_str[13];
        time_db(&(m_minDose -> time_p), time_str);
        sprintf(sqlcmd, "INSERT INTO MinimalDose(t, min_dose) VALUES (interval (3) \'%s\', %d) ON CONFLICT DO NOTHING", time_str, m_minDose -> daily_dose);

        m_minDose -> daily_dose = 0;
        res = (*db).ExecSQLcmd(sqlcmd);
        PQclear(res);
    }
}