#include "monitor.h"

int main(int argc, char* argv[]){
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    PGresult* res;
    char sqlcmd[1000];

    struct m_safety m_safety = {0, {0}};
    struct m_liveness m_liveness = {0, 0, {0}};
    struct m_minDose m_minDose = {0, 0, {0}};

    sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid = tv.vid AND tv.varname = 'G'");

    res = db.ExecSQLtuples(sqlcmd);
    int n_rows_g = PQntuples(res); 

    while(m_safety.tuples_read < n_rows_g){
        double gluc_val = stod(PQgetvalue(res, m_safety.tuples_read, PQfnumber(res, "varvalue")));
        monitor_safety(&db, &m_safety, gluc_val);
        monitor_liveness(&db, &m_liveness, gluc_val);
    }

    PQclear(res);

    sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid = tv.vid AND tv.varname = 'comp_dose'");

    res = db.ExecSQLtuples(sqlcmd);
    int n_rows_dose = PQntuples(res); 

    while(m_minDose.tuples_read < n_rows_dose){

        int comp_dose = stod(PQgetvalue(res, m_minDose.tuples_read, PQfnumber(res, "varvalue")));
        monitor_minimalDose(&db, &m_minDose, comp_dose);
    }

    PQclear(res);

}