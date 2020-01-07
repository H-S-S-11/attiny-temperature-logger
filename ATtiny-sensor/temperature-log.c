#include <avr/power.h>
#include "usi_i2c_master.h"
#include "24FC512.h"

int main(){

    clock_prescale_set(16);
    char data[] = {0x00, 0x00, 0x00, 0x1a, 0x2b, 0xc3, 0xd4, 0xe5, 0xf6};
    
    while(1){

        write_page_24xx512( 0x00, 0x0001, data, 9);
        _delay_ms(1000);
    }
}