#include "DS1307.h"

void read_time_DS1307(char *rx_buffer){
    char write_pointer[] = { ADDRESS_DS1307, 0x00 };
    USI_I2C_Master_Start_Transmission(write_pointer, 2);
    rx_buffer[0] = ADDRESS_DS1307 | 0x01; //read command
    USI_I2C_Master_Start_Transmission(rx_buffer, 8);
}