#ifndef i2c

#define i2c
#include <avr/io.h>

void i2c_init_master();
void i2c_start_condition();
uint8_t i2c_master_send_byte(uint8_t data);
void i2c_stop_condition();

#endif