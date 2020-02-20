#include "DS1307.h"

void read_time_DS1307(char buf[]){
    char write_pointer[2] = { ADDRESS_DS1307, 0x00 };
    USI_I2C_Master_Start_Transmission(write_pointer, 2);
    buf[0] = ADDRESS_DS1307 | 0x01; //read command
    USI_I2C_Master_Start_Transmission(buf, 8);
}

void set_seconds_DS1307(char seconds){
    char command[3] = { ADDRESS_DS1307, 0x00, seconds };
    USI_I2C_Master_Start_Transmission(command, 3);
}