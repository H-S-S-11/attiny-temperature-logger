#ifndef EEPROM_24FC512

#include <avr/io.h>
#include "usi_i2c_master.h"
#define EEPROM_24FC512

#define ADDRESS_24xx512 0xa0

void write_byte_24xx512(char cs_bits, uint16_t address, char byte);

//page writes up to 128 bytes
//leave three blank spaces at the start of the array, include this in length
void write_page_24xx512(char cs_bits, uint16_t start_address, char *byte_array, char length);

#endif