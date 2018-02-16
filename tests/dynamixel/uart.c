#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "axpacket.h"

#define CLOCK_FQ 16000000

void USART0_init(uint32_t baud)
{
	unsigned int temp_baud = 0;
	
	DDRE |= 1 << 1; // TX0 pin is output
	DDRE &= ~(0x1); // RX0 pin is input
	
	temp_baud = (CLOCK_FQ / (8 * baud)) - 1;
	
	UBRR0H = (unsigned char) (temp_baud >> 8);
	UBRR0L = (unsigned char) temp_baud;
	
	UCSR0A = 1 << U2X0;
	
	//enable RX, enable TX, UCSZ02 -> for data size
	UCSR0B = (1 << RXEN0) | (1 << TXEN) | (0 << UCSZ02);
	
	// async, no parity, 1 stop bit, 8 bit data size	
	UCSR0C = (0 << 7) | (0 << UMSEL0) | (0 << UPM01) 
		   | (0 << UPM00) | (0 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
}

void USART0_transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( ! ( UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void usart0_axpacket_send(t_axPacket* packet)
{
	USART0_transmit(packet->sync_1);
	USART0_transmit(packet->sync_2);
	USART0_transmit(packet->ax_id);
	USART0_transmit(packet->length);
	USART0_transmit(packet->instruction);
	
	int i;
	for(i=0; i<packet->length-2; i++)
	{
		USART0_transmit(packet -> parameters[i]);
	}
	
	USART0_transmit(packet->checksum);
}
