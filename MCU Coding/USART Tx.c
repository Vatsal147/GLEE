/*
 * USART implement in Atmega328p.c
 *
 * Created: 24-12-2020 22:53:59
 * Author : VATSAL
 */ 

#define F_CPU 8000000UL
#define BAUD 9600  
#define BAUDRATE 51   //((F_CPU)/(16UL * BAUD) - 1)

#include <avr/io.h>
#include <util/delay.h>

void USART_initial(void){
	//setting baud rates
    UBRR0H = (BAUDRATE >> 8);  // writing to lower byte  (masking kiya to set baud rate in lower wala as 51 < 255 to pura usme aa jayega)
	UBRR0L = BAUDRATE;    // writing to higher byte (pura  byte shift kiya to make upper wala empty)
    
	//enabling USART receiver and transmitter
	UCSR0B |= (1 << TXEN0);  /* isase 1 aa jayega TXEN0 and RXEN0 bit wali positions pe and then or lenge to vo dono positions pe 1 aa jayega
														overriding normal receiver-transmitter function */
	
	// setting frame format
	UCSR0C |= (0 << USBS0)|(1 << UCSZ00)|(1 << UCSZ01);		//default is 8 data bits, no parity bit, 1 stop bit
}   

void USART_trans(unsigned char data){
	
	//Check if the transmit buffer is empty or not by empty while loop.  Here UDRE represents USART Data Register Empty Flag
	while(!(UCSR0A & (1 << UDRE0)));  // as soon as the condition inside becomes false, it will move ahead
	
	UDR0 = data; // UDR represents transmit buffer in which now we will send data
}

int main(void)
{
	// initialize USART
	USART_initial();
	unsigned char data = 'a';   // transmit data
	
	while (1)
	{
	USART_trans(data);
	_delay_ms(1000);
	}
}

