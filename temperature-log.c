#include <avr/power.h>
#include "usi_i2c_master.h"

int main(){

    clock_prescale_set(16);
    char command[] = {0xa0, 0x00, 0x01, 0x1a, 0x2b, 0xc3, 0xd4, 0xe5, 0xf6};
    
    while(1){

        USI_I2C_Master_Start_Transmission(command, 9);
        _delay_ms(1000);
    }
}