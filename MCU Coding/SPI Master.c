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

//Initialize USART
void USART_initial(void){
	//setting baud rates
    UBRR0H = (BAUDRATE >> 8);  
	UBRR0L = BAUDRATE;    
    
	//enabling USART receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);  
	
	// setting frame format
	UCSR0C |= (0 << USBS0)|(1 << UCSZ00)|(1 << UCSZ01);		//default is 8 data bits, no parity bit, 1 stop bit
} 

//USART data reception
unsigned char USART_rec(void){
	
	while (!(UCSR0A & (1<<RXC0))); //Checking if register is empty
	
	return UDR0;  // receiving data
}

void USART_trans(unsigned char data){
	
	//Check if the transmit buffer is empty or not by empty while loop.  Here UDRE represents USART Data Register Empty Flag
	while(!(UCSR0A & (1 << UDRE0)));  // as soon as the condition inside becomes false, it will move ahead
	
	UDR0 = data; // UDR represents transmit buffer in which now we will send data
}

// Initialize master
void spi_mast_init(void){  
	
	DDRB |= (1 << DDB2) | (1 << DDB1) | (1 << DDB0); // In portB, setting MOSI, SCK and SS resp. as output (MOSI is 3 and SCK is 5 in 328PB)
	
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);  //enable SPI,  set as master,  set SCK Fq as Fosc/16,  
	
}

void spi_mast_trans(unsigned char data){
	//sending data
	SPDR = data;
	
	// checking last transmission is completed or not
	while(!(SPSR & (1 << SPIF)));
}

unsigned char spi_mast_rec(void){
	//Checking if last reception is completed or not
	while(!(SPSR & (1 << SPIF)));
	
	//returning the received data
	return SPDR;
}

int main(void)
{
	//initialize USART
	USART_initial();
    //initialize SPI master
	spi_mast_init();
	
    while (1) 
    {
		spi_mast_trans(USART_rec());	
		//_delay_ms(200);
		USART_trans(spi_mast_rec());
		
		// _delay_ms(200);
    }
}

