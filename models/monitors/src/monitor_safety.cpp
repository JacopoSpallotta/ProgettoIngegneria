
#include <monitor.h>

int main(int argc, char* argv[]){
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    PGresult* res;
    int tuples_read = 1;
    double gluc_val = 0;
    char sqlcmd[1000];
    
    while(1){
        sprintf(sqlcmd, "SELECT l.varvalue FROM logtable l, timevar tv WHERE l.vid=tv.vid AND tv.varname = 'G' ");

        res = db.ExecSQLtuples(sqlcmd);
        int rows = PQntuples(res);
        cout<<rows<<endl;
        if(rows > tuples_read){
            gluc_val = stod(PQgetvalue(res, rows-1, PQfnumber(res, "varvalue")));
            PQclear(res);
            tuples_read++;

            sprintf(sqlcmd, "INSERT INTO MonitorTable VALUES (%d) ON CONFLICT DO NOTHING", gluc_val < 50);
            res = db.ExecSQLcmd(sqlcmd);
            PQclear(res);
        }
        usleep(5000);

    }
}