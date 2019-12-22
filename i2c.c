#include "i2c.h"

void i2c_init_master(){
    USICR = 0x22;   //Two-wire mode with software clock
    MCUCR &= ~_BV(PUD); //enable pullups
    DDRB &= ~_BV(PB0) & ~_BV(PB2); //inputs with tristate
    PORTB &= ~_BV(PB0) & ~_BV(PB2);
}

void i2c_start_condition(){
    //pull SDA low
    DDRB |= _BV(PB0);  
    //pull SCL low
    DDRB |= _BV(PB2);
}

uint8_t i2c_master_send_byte(uint8_t data){
    USIDR = data;
    uint8_t ack = 0;
    uint8_t i;
    for (i = 0; i < 7; i++){
        //pull SCL high
        PORTB |= _BV(PB2);
        //pull SCL low
        PORTB &= ~_BV(PB2);
        //shift data
        USICR |= _BV(USICLK);
    }
    //Pull SCL high
    PORTB |= _BV(PB2);
    
    //all data sent
    //ack cycle
    //pull SCL low
    PORTB &= ~_BV(PB2);
    //Release SDA
    DDRB &= ~_BV(PB0);
    //Pull SCL high
    PORTB |= _BV(PB2);
    if(!(PINB & _BV(PB0))){
        ack = 1;
    }
    //pull SCL low
    DDRB |= _BV(PB2);
    //control SDA
    DDRB |= _BV(PB0);
    return ack;
}

void i2c_stop_condition(){
    //pull SCL high
    PORTB |= _BV(PB2);
    //release SCL
    DDRB &= ~_BV(PB2);
    //release SDA
    DDRB &= ~_BV(PB0);
}
