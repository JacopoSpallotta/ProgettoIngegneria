#include "main.h"

typedef enum {idle,test,execution,fault} insulin_pump_state;
typedef struct Insulin_Pump{
    const int MIN_GLUCOSE;
    const int AVERAGE_GLUCOSE;

    insulin_pump_state state;
    double prev_glucose;
    int t_old;
};