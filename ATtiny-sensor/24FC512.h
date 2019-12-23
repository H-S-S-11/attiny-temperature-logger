#ifndef EEPROM_24FC512

#include <avr/io.h>
#include "i2c.h"
#define EEPROM_24FC512

#define ADDRESS_24xx512 0x60

void write_byte_24xx512(uint8_t cs_bits, uint16_t address, uint8_t byte);

//page writes up to 128 bytes
void write_page_24xx512(uint8_t cs_bits, uint16_t address, uint8_t *byte_array, uint8_t length);

#endif