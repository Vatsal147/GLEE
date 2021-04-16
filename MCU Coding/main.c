/*
 * TWI MT in Atmega128.c
 *
 * Created: 11-02-2021 21:49:39
 * Author : VATSAL
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define BAUDRATE 51   //((F_CPU)/(16UL * BAUD) - 1)


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

void TWI_mast_initial(void){
	
	TWBR = 0x20;  //setting value of bit rate register
	TWSR = (0 << TWPS0) | (0 << TWPS1); //setting prescaler bits 0,0 to set prescalar value as 1
	// SCL = F_CPU/(16 + 2*TWBR*4^(TWPS))
}

void TWI_start(void){
	TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT) ; //Enable TWI transmission, Send start bit, clear the interrupt flag 
	
	while(!(TWCR & (1 << TWINT))); // indicates start condition is sent
	
	// while ((TWSR & 0xF8) != 0x08);   //checking is start condition is sent or not
	//error;                      // display an error is not
}

void TWI_mast_send_address(uint8_t address){
	
	TWDR = address; //slave address + write condition
	
	TWCR = (1 << TWINT) | (1 << TWEN);  //clearing interrupt flag to send SLA_W
	
	while(!(TWCR & (1 << TWINT)));  // checking if the interrupt flag is set to make sure above data is sent
	
	// while ((TWSR & 0xF8) != 0x18);     //check if status reg shows data is sent
	//error                    // otherwise display error
}

void TWI_mast_send_data(uint8_t data){
	
	TWDR = data;  //sending data bits
	
	TWCR = (1 << TWINT) | (1 << TWEN);  // clearing interrupt flag to send data
	
	while(!(TWCR & (1 << TWINT)));  // checking if the interrupt flag is set to make sure above data is sent
	
	// while ((TWSR & 0xF8) != 0x28);     //check if status reg shows data is sent
	//error                    // otherwise display error
	
}

void TWI_stop(void){
	
	TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN); //transmitting stop bit, clear flag, enable twi
	
	// while (!(TWCR & (1 << TWSTO))); // wait till stop is transmitted
}



int main(void)
{
	// USART_initial();
    /* Replace with your application code */
	// unsigned char data;
	
	// data = USART_rec();
	 
	TWI_mast_initial();
	
	TWI_start();
	
	TWI_mast_send_address(0x20);	
	
	TWI_mast_send_data(79);
	
	TWI_stop();
	
	// while(1);
    // while (1) 
    // {
    // }
}

