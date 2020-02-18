#ifndef TEMP_MCP9801

#include <avr/io.h>
#include "usi_i2c_master.h"
#define TEMP_MCP9801

#define ADDRESS_MCP9801 0x90

void set_pointer_ta(char cs_bits);

uint16_t read_register(char cs_bits);

void write_config(char cs_bits, char config_data);

#endif