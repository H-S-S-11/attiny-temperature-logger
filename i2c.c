#include "i2c.h"

void i2c_init_master(){
    USICR = 0x20;   //Two-wire mode
    MCUCR &= ~_BV(PUD); //enable pullups
    DDRB &= ~_BV(SDA) & ~_BV(SCL); //inputs with pullup
    PORTB |= _BV(SDA) | _BV(SCL);
}

void i2c_start_condition(){
    //control data lines, pull SDA low, pull SCL low
    PORTB |= _BV(SDA) | _BV(SCL);
    DDRB |= _BV(SDA) | _BV(SCL);  
    PORTB &= ~_BV(SDA);
    _delay_us(I2C_DELAY);
    PORTB &= ~_BV(SCL);
    _delay_ms(I2C_DELAY);
}

uint8_t i2c_master_send_byte(uint8_t data){

    

    USIDR = data;
    uint8_t ack = 0;

    uint8_t i;
    for (i = 0; i < 8; i++){
        
        //Setup data
        if ( data & _BV(i) ){
            PORTB |= _BV(SDA);
        } else {
            PORTB &= ~_BV(SDA);
        }


        //pull SCL high
        _delay_us(I2C_DELAY);
        PORTB |= _BV(SCL);
        //pull SCL low
        _delay_us(I2C_DELAY);
        PORTB &= ~_BV(SCL);
    }

    /* using USICLK
    uint8_t i;
    for (i = 0; i < 8; i++){
        //pull SCL high
        _delay_us(I2C_DELAY);
        PORTB |= _BV(SCL);
        //pull SCL low
        PORTB &= ~_BV(SCL);
        //shift data
        USICR |= _BV(USICLK);
    }
    */

   /*
    //credit https://github.com/JDat/AtTiny-I2C-master-slave-USI/blob/master/usi_i2c_master.c
    // Shift Data
    USISR = 0b11110000 | (0x00<<USICNT0);
	do
	{
		_delay_us(I2C_DELAY);
		USICR = 0b00101011;							//SCL Positive Edge
		while (!(PINB&(_BV(SCL))));		            //Wait for SCL to go high
		_delay_us(I2C_DELAY);
		USICR = 0b00101011; 						//SCL Negative Edge
	} while (!(USISR&(_BV(USIOIF))));				//Do until transfer is complete
    _delay_us(I2C_DELAY);


    //ack cycle
    DDRB &= ~_BV(SDA);
    USISR = 0b11110000 | (0x0E<<USICNT0);
	do
	{
		_delay_us(I2C_DELAY);
		USICR = 0b00101011;							//SCL Positive Edge
		while (!(PINB&(_BV(SCL))));		            //Wait for SCL to go high
		_delay_us(I2C_DELAY);
		USICR = 0b00101011;  						//SCL Negative Edge
	} while (!(USISR&(_BV(USIOIF))));				//Do until transfer is complete
    _delay_us(I2C_DELAY);

	if(USIDR & 0x01)
	{
		PORTB |= _BV(SCL);
		PORTB |= _BV(SDA);
		ack = 0;
	}

	DDRB |= _BV(SDA);
    */
    
    //ack
    //Release SDA
    DDRB &= ~_BV(SDA);
    //Pull SCL high
    _delay_us(I2C_DELAY);
    PORTB |= _BV(SCL);
    if(!(PINB & _BV(SDA))){
        ack = 1;
    }
    //pull SCL low
    DDRB |= _BV(SCL);
    //control SDA
    DDRB |= _BV(SDA);
    

    return ack;

}

void i2c_stop_condition(){
    //SDA low
    PORTB &= ~_BV(SDA);
    //pull SCL high
    _delay_us(I2C_DELAY);
    PORTB |= _BV(SCL);
    //release SCL
    DDRB &= ~_BV(SCL);

    _delay_us(I2C_DELAY);
    //SDA high, release
    PORTB |= _BV(SDA);
    DDRB &= ~_BV(SDA);
}
