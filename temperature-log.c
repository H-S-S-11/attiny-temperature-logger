#include "24FC512.h"
#include "i2c.h"
#include <avr/power.h>
#include <util/delay.h>

#define F_CPU 500000

int main(){

    
    clock_prescale_set(16);
    
    i2c_init_master();

    i2c_start_condition();
    i2c_master_send_byte(0xa0);
    i2c_master_send_byte(0x00);
    i2c_master_send_byte(0x00);
    i2c_master_send_byte(0x3c);
    i2c_master_send_byte(0xd4);
    i2c_master_send_byte(0xe5);
    i2c_stop_condition();


    while(1){

        _delay_ms(1000);

        i2c_start_condition();
        i2c_master_send_byte(0xa0);
        i2c_master_send_byte(0x00);
        i2c_master_send_byte(0x00);
        i2c_master_send_byte(0x3c);
        i2c_master_send_byte(0xd4);
        i2c_master_send_byte(0xe5);
        i2c_stop_condition();

        
    }
}