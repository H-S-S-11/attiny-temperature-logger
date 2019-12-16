#ifndef 24FC512

#include <avr/io.h>
#define 24FC512

void 24xx512_write_byte(uint8_t cs_bits, uint16_t address, uint8_t byte);

//page writes up to 128 bytes
void 24xx512_write_page(uint8_t cs_bits, uint16_t address, uint8_t *byte_array, uint8_t length);

#endif