#include "monitor.h"

int main(int argc, char* argv[]){
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    PGresult* res;
    char sqlcmd[1000];

    struct m_safety m_safety = {0, {0}};
    struct m_liveness m_liveness = {0, 0, {0}};
    struct m_minDose m_minDose = {0, 0, {0}};

    while(get_time(&(m_safety.time_p)) <= MINUTES_PER_DAY){
    
        sprintf(sqlcmd, "SELECT count(*) FROM logtable l, timevar tv WHERE l.vid = tv.vid AND tv.varname = 'G'");

        res = db.ExecSQLtuples(sqlcmd);
        int n_rows_g = atoi(PQgetvalue(res, 0, 0));
        PQclear(res);

        if(n_rows_g > m_safety.tuples_read){
            sprintf(sqlcmd, "SELECT l.t, l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'G' ORDER BY l.t DESC LIMIT 1");
            res = (db).ExecSQLtuples(sqlcmd);

            double gluc_val = stod(PQgetvalue(res, 0, PQfnumber(res, "varvalue")));
            PQclear(res);

            monitor_safety(&db, &m_safety, gluc_val);
            monitor_liveness(&db, &m_liveness, gluc_val);
        }

        sprintf(sqlcmd, "SELECT count(*) FROM logtable l, timevar tv WHERE l.vid = tv.vid AND tv.varname = 'comp_dose'");

        res = db.ExecSQLtuples(sqlcmd);
        int n_rows_dose = atoi(PQgetvalue(res, 0, 0));
        PQclear(res);

        if(n_rows_dose > m_minDose.tuples_read){
    
            sprintf(sqlcmd, "SELECT l.t, l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'comp_dose' ORDER BY l.t DESC LIMIT 1");
            res = db.ExecSQLtuples(sqlcmd);
            int comp_dose = stod(PQgetvalue(res, 0, PQfnumber(res, "varvalue")));
            PQclear(res);

            monitor_minimalDose(&db, &m_minDose, comp_dose);
        }
        cout<<get_time(&(m_safety.time_p))<<endl;
        usleep(500*T);
    }
}