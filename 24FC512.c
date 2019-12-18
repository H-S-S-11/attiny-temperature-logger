#include "24FC512.h"


void 24xx512_write_byte(uint8_t cs_bits, uint16_t address, uint8_t byte){
    uint8_t control_byte = 24xx512_ADDRESS | (cs_bits << 1);
    uint8_t address_high = address >> 8;
    uint8_t address_low = address & 0x00ff;

}

void 24xx512_write_page(uint8_t cs_bits, uint16_t address, uint8_t *byte_array, uint8_t length){
    
}