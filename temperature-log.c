#include "24FC512.h"
#include "i2c.h"
#include <avr/power.h>

int main(){

    clock_prescale_set(16);

    MCUCR &= ~_BV(PUD);
    DDRB &= ~_BV(SDA) & ~_BV(SCL); //inputs with pullup
    PORTB |= _BV(SDA) | _BV(SCL);
    //i2c_init_master();

    while(1){
        i2c_start_condition();
        i2c_master_send_byte(0xa0);
        i2c_master_send_byte(0x00);
        i2c_master_send_byte(0x01);
        i2c_master_send_byte(0x1a);
        i2c_master_send_byte(0x2b);
        i2c_master_send_byte(0xc3);
        i2c_stop_condition();
        _delay_ms(1000);
    }
}