#include "24FC512.h"


void write_byte_24xx512(uint8_t cs_bits, uint16_t address, uint8_t byte){
    uint8_t control_byte = ADDRESS_24xx512 | (cs_bits << 1);
    uint8_t address_high = address >> 8;
    uint8_t address_low = address & 0x00ff;

}

void write_page_24xx512(uint8_t cs_bits, uint16_t address, uint8_t *byte_array, uint8_t length){
    
}