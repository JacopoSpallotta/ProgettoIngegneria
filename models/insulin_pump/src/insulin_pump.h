#include "main.h"

typedef enum {idle,test,execution} insulin_pump_state;
typedef struct Insulin_Pump{
    const int HARD_MIN_GLUCOSE;
    const int SAFE_MIN_GLUCOSE;
    const int HARD_MAX_GLUCOSE;
    const int SAFE_MAX_GLUCOSE;
    
    insulin_pump_state state;
    double comp_dose;
    double prev_glucose;
    double prev_prev_glucose;
    double sum_insulin;
}Insulin_Pump;