#include <avr/power.h>
#include "usi_i2c_master.h"
#include "24FC512.h"
#include "MCP9801.h"

int main(){

    clock_prescale_set(16);
    char data[] = { 0x00, 0x00, 0x00, 0x1a, 0x2b };
    uint16_t start_address = 1;
    uint16_t temperature;

    set_pointer_ta( 0x00 );

    
    while(1){

        temperature = read_ta( 0x00 );
        data[3] = (temperature >> 8);
        data[4] = temperature & 0x00ff;        
        write_page_24xx512( 0x00, start_address, data, 9);
        start_address += 2;

        _delay_ms(1000);
    }
}