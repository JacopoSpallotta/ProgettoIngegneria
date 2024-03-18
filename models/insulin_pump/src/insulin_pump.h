#include "main.h"

typedef enum {idle,test,compute_release} insulin_pump_state;
typedef struct Insulin_Pump{
    insulin_pump_state state;
    double glucose_level;
    double prev_glucose;
    double prev_prev_glucose;
}Insulin_Pump;