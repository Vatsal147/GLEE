/*
 * GccApplication1.c
 *
 * Created: 23-12-2020 20:11:03
 * Author : VATSAL
 */ 
#ifndef F_CPU
#define F_CPU 8000000 // 8 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF; //Makes PORTB as Output
	while(1) //infinite loop
	{
		PORTB = 0b00000001; //Turns ON LED B0
		_delay_ms(500); //0.5 second delay
		PORTB = 0b00000011; //LED B0, B1
		_delay_ms(500);
		PORTB = 0b00000111; // LED B0, B1, B2
		_delay_ms(500);
		PORTB = 0b00001010; // LED B1, B3
		_delay_ms(500);
	}
}

