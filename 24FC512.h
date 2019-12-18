#ifndef 24FC512

#include <avr/io.h>
#include "i2c.h"
#define 24FC512

#define 24xx512_ADDRESS 0x60

void 24xx512_write_byte(uint8_t cs_bits, uint16_t address, uint8_t byte);

//page writes up to 128 bytes
void 24xx512_write_page(uint8_t cs_bits, uint16_t address, uint8_t *byte_array, uint8_t length);

#endif