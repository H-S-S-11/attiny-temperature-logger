#include <avr/power.h>
#include "usi_i2c_master.h"
#include "24FC512.h"
#include "MCP9801.h"
#include "DS1307.h"

int main(){

    clock_prescale_set(clock_div_16);

    //3 bytes of write command
    //2 for temperature
    //6 for date/time
    char eeprom_write_data[11];
    char date_time[8] = {0};
    uint16_t start_address = 1;
    uint16_t temperature;

    set_pointer_ta( 0x00 );
    set_seconds_DS1307( 0 );
    
    while(1){

        do{
            temperature = read_ta( 0x00 );
        }while(temperature >= 0xff80);
        
        read_time_DS1307(date_time);

        eeprom_write_data[3] = (char)(temperature >> 8);
        eeprom_write_data[4] = (char)temperature & 0x00ff;
        eeprom_write_data[5] = date_time[1]; //seconds
        eeprom_write_data[6] = date_time[2]; //minutes
        eeprom_write_data[7] = date_time[3]; //hours
        eeprom_write_data[8] = date_time[5]; //date
        eeprom_write_data[9] = date_time[6]; //month
        eeprom_write_data[10]= date_time[7]; //years
    
        write_page_24xx512( 0x00, start_address, eeprom_write_data, 11);
        start_address += 8;

        _delay_ms(10000);
    }
}