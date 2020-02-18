#include "MCP9801.h"

void set_pointer_ta(char cs_bits){
    char control_byte = ADDRESS_MCP9801 | (cs_bits << 1);
    char command = { control_byte, 0x00 };
    USI_I2C_Master_Start_Transmission(command, 2);
}

uint16_t read_ta(char cs_bits){
    char control_byte = ADDRESS_MCP9801 | (cs_bits << 1) | 0x01;
    char command[3] = { control_byte, 0x00, 0x00 }; //rx buffer
    USI_I2C_Master_Start_Transmission(command, 3)
}

void write_config(char cs_bits, char config_data){
    char control_byte = ADDRESS_MCP9801 | (cs_bits << 1);
    char command = { control_byte, 0x01, config_data };
    USI_I2C_Master_Start_Transmission(command, 3);
}