/*    
    Copyright (C) 2019 Elia Ritterbusch 

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "i2c_master.h"

#define MCP24FC512_WRITE 0xA0
#define MCP24FC512_READ 0xA1
#define MCP9801_READ 0x91
#define DS1307_WRITE 0xD0
#define DS1307_READ 0xD1

void init_uart0(void)
{
	/* Configure 9600 baud, 8-bit, no parity and one stop bit */
	const int baud_rate = 9600;
	UBRR0H = (F_CPU/(baud_rate*16L)-1) >> 8;
	UBRR0L = (F_CPU/(baud_rate*16L)-1);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

char get_ch(void)
{
	while(!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

void put_ch(char ch)
{
	while (!(UCSR0A & _BV(UDRE0)));
	UDR0 = ch;
}

void put_str(char *str)
{
	int i;
	for(i=0; str[i]; i++) put_ch(str[i]);
}


uint8_t read_data(uint8_t address[2]){
	put_str("Reading \n");
	uint8_t return_data;

	i2c_start(MCP24FC512_WRITE);
	i2c_write(address[0]); // set pointer to address
	i2c_write(address[1]);
	
	i2c_start(MCP24FC512_READ);

	return_data = i2c_read_nack();

	i2c_stop();

	return return_data;
}

int main(void){
	
	init_uart0();
	i2c_init();
		
	uint8_t recieved_data[8];
	uint16_t address = 0x0001;
	uint8_t address_buf[] = {0x00,0x00};
	char buffer[40];
	uint8_t i;
	uint8_t seconds;
	uint8_t minutes;
	//uint8_t to_send[3] = {0xab, 0xdc, 0x12};

	i2c_start(DS1307_WRITE);
	i2c_write(0x00);
	i2c_write(0x00);
	i2c_stop();


	while(1){

		address_buf[0] = (uint8_t)address >> 8;
		address_buf[1] = (uint8_t)address & 0x00ff;
		address += 8;

		i2c_start(MCP24FC512_WRITE);
		i2c_write(address_buf[0]); // set pointer to address
		i2c_write(address_buf[1]);
		
		i2c_start(MCP24FC512_READ);

		for( i = 0; i < 7; i++){
			recieved_data[i] = i2c_read_ack();
		}

		recieved_data[7] = i2c_read_nack();

		i2c_stop();

		i2c_start(MCP9801_READ);
		recieved_data[6] = i2c_read_ack();
		recieved_data[7] = i2c_read_nack();
		i2c_stop();

		i2c_start(DS1307_WRITE);
		i2c_write(0x00);
		i2c_stop();

		i2c_start(DS1307_READ);
		seconds = i2c_read_ack();
		minutes = i2c_read_nack();
		i2c_stop();

		recieved_data[4] = seconds;
		recieved_data[5] = minutes;

		sprintf(buffer, "%x %x %x %x %x %x %x %x\n\r", recieved_data[0], recieved_data[1],
			recieved_data[2], recieved_data[3], recieved_data[4], recieved_data[5],
			recieved_data[6], recieved_data[7]);

		put_str(buffer);	
		
		_delay_ms(1000);
	}
	
	return 0;
}
