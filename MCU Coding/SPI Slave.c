/*
 * SPI in Atmega128.c
 *
 * Created: 14-01-2021 22:14:12
 * Author : VATSAL
 */ 

#define F_CPU 8000000UL
#define BAUD 9600
#define BAUDRATE 51   //((F_CPU)/(16UL * BAUD) - 1)

#include <avr/io.h>
#include <util/delay.h>


void spi_slav_init(void){
	
	DDRB |= (1 << DDB3); // In port B, setting MISO (MISO is 4 in 328PB)
	
	SPCR |= (1 << SPE); //Enable SPI
}

unsigned char spi_slav_rec(void){
	
	//Checking if last transmission is completed or not
	while(!(SPSR & (1 << SPIF)));
	
	//returning the received data
	return SPDR; 	
}

void spi_slav_trans(unsigned char data){
	
	//sending data
	SPDR = data;
	// checking if transmission is completed
	while(!(SPSR & (1 << SPIF)));
}

//Initialize USART
void USART_initial(void){
	//setting baud rates
	UBRR0H = (BAUDRATE >> 8);
	UBRR0L = BAUDRATE;
	
	//enabling USART receiver and transmitter
	UCSR0B |= (1 << TXEN0);
	
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
    //initialize SPI slave
	spi_slav_init();
	//Initialize USART
	// USART_initial();
	
    while (1) 
    {
		// USART_trans(spi_slav_rec());
		
		spi_slav_trans(spi_slav_rec());
		
		//_delay_ms(200);
    }
}

