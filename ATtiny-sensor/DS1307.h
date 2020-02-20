#ifndef RTC_DS1307

#include <avr/io.h>
#include "usi_i2c_master.h"
#define RTC_DS1307

#define ADDRESS_DS1307 0xd0

//leave one blank space at the start of buffer
//followed by 7 bytes for date and time (6 used+ day)
void read_time_DS1307(char *rx_buffer);

#endif