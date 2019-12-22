#include "24FC512.h"
#include "i2c.h"
#include <avr/power.h>

int main(){

    clock_prescale_set(16);
    
    i2c_init_master();
    while(1){
        i2c_start_condition();
        i2c_master_send_byte(0xaa);
        i2c_stop_condition();
    }
}