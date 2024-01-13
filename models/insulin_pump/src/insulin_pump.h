#include "main.h"

typedef enum {idle,test,execution,fault} insulin_pump_state;
typedef struct Insulin_Pump{
    const int HARD_MIN_GLUCOSE;
    const int SAFE_MIN_GLUCOSE;
    const int HARD_MAX_GLUCOSE;
    const int SAFE_MAX_GLUCOSE;
    
    insulin_pump_state state;
    double prev_glucose;
    double prev_prev_glucose;
    int t_old;
};