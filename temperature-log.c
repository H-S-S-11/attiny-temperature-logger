#include "usi_i2c_master.h"
#include <avr/power.h>
#include <util/delay.h>

int main(){
    //500kHz clock
    clock_prescale_set(16);
    uint8_t eeprom_write_addr = 0xa0;
    char i2c_message[6] = { eeprom_write_addr, 0x00, 0x00, 0x1a, 0x2b, 0x3c };
    
    while(1){
        USI_I2C_Master_Transceiver_Start(i2c_message, 6);
        _delay_ms(1000);
    }
}