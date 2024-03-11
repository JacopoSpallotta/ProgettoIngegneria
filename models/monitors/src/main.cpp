#include "monitor.h"

int main(int argc, char* argv[]){
    Con2DB db("localhost","5432", "insulin_pump", "47002", "logdb_insulin_pump");
    struct m_safety m_safety = {1, {0}};
    struct m_liveness m_liveness = {1,0, {0}};
    struct m_minDose m_minDose = {1,0, {0}};

    while(get_time(&(m_safety.time_p)) <= MINUTES_PER_DAY){
        monitor_safety(&db, &m_safety);
        monitor_liveness(&db, &m_liveness);
        monitor_minimalDose(&db, &m_minDose);
        usleep(900);
    }
}