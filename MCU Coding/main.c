/*
 * TWI SR in Atmega128.c
 *
 * Created: 13-02-2021 17:13:46
 * Author : VATSAL
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define BAUDRATE 51   //((F_CPU)/(16UL * BAUD) - 1)


void USART_initial(void){
	//setting baud rates
	UBRR0H = (BAUDRATE >> 8);
	UBRR0L = BAUDRATE;
	
	//enabling USART receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	// setting frame format
	UCSR0C |= (0 << USBS0)|(1 << UCSZ00)|(1 << UCSZ01);		//default is 8 data bits, no parity bit, 1 stop bit
}

void USART_trans(unsigned char data){
	
	//Check if the transmit buffer is empty or not by empty while loop.  Here UDRE represents USART Data Register Empty Flag
	while(!(UCSR0A & (1 << UDRE0)));  // as soon as the condition inside becomes false, it will move ahead
	
	UDR0 = data; // UDR represents transmit buffer in which now we will send data
}


void TWI_slave_init(void){
	
	TWAR = 0x20;
	TWCR = (1 << TWEN) | (1 << TWEA) | (0 << TWSTA) |  (0 < TWSTO) | (1 << TWINT);
}

void TWI_match_slav_address(void){
	
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 < TWEA); // enable TWI, clear interrupt flag, enable acknowledgment bit
	while(!(TWCR & (1 << TWINT)));                         //waiting for flag to get set
	// while((TWSR & 0xF8)!= 0x60);                       //check is ACK bit is sent back
}

uint8_t TWI_slave_read_data(void){
	
	uint8_t rec;
	// TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEN);  //enable twi, interrupt flag, ack bit
	while(!(TWCR & (1 << TWINT)));                   //wait for flag to set 
	rec = TWDR;         // read received data
	// while((TWSR & 0xF8) != 0x80);       //check if data is recieved and ack is sent 
	return rec;
}


int main(void)
{
	// USART_initial();
	// unsigned char data;
	uint8_t data;
	
	TWI_slave_init();
	
	TWI_match_slav_address();
	
	data = TWI_slave_read_data();
	
	DDRB = 0xff;
	PORTB= data;
	
	// USART_trans(data);
	
	// while(1);
	
}

