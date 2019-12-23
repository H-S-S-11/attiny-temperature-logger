#include "24FC512.h"


void write_byte_24xx512(char cs_bits, uint16_t address, char byte){
    char control_byte = ADDRESS_24xx512 | (cs_bits << 1);
    char address_high = address >> 8;
    char address_low = address & 0x00ff;
    char command[] = { control_byte, address_high, address_low, byte};
    USI_I2C_Master_Start_Transmission(command, 4);
}

void write_page_24xx512(char cs_bits, uint16_t start_address, char *byte_array, char length){
    char control_byte = ADDRESS_24xx512 | (cs_bits << 1);
    char address_high = start_address >> 8;
    char address_low = start_address & 0x00ff;
    byte_array[0] = control_byte;
    byte_array[1] = address_high;
    byte_array[2] = address_low;
    USI_I2C_Master_Start_Transmission(byte_array, length);    
}