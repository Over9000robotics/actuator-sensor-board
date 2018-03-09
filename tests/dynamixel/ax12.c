#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "axpacket.h"
#include "ax12.h"
#include "usart0.h"

#define CLOCK_FQ 16000000


int main(void)
{
	cli();
	
	USART0_init(1000000);
	
	sei();
	
	_delay_ms(2000);
	
	/*
	axpacket_prepare(BROADCASTING_ID, INST_WRITE, P_LED);
	axpacket_put_byte(1);
	axpacket_end();
	*/
/*	
	USART0_transmit(0xFF);
	USART0_transmit(0xFF);
	USART0_transmit(BROADCASTING_ID);
	USART0_transmit(0x07);
	USART0_transmit(0x03);
	USART0_transmit(0x1E);
	USART0_transmit(0x00);
	USART0_transmit(0x02);
	USART0_transmit(0x00);
	USART0_transmit(0x02);
	USART0_transmit(0xD5);
*/
	
	//set ID to 1
	USART0_transmit(0xFF);
	USART0_transmit(0xFF);
	USART0_transmit(BROADCASTING_ID);
	USART0_transmit(0x04);
	USART0_transmit(0x03);
	USART0_transmit(0x03);
	USART0_transmit(0x01);
	USART0_transmit(0xF6);
	
	while(1)
	{
		/*
	axpacket_prepare(BROADCASTING_ID, INST_WRITE, P_LED);
	axpacket_put_byte(0);
	axpacket_end();
	
	_delay_ms(1500);
	
	axpacket_prepare(BROADCASTING_ID, INST_WRITE, P_LED);
	axpacket_put_byte(1);
	axpacket_end();
	
	_delay_ms(1500);
	* */
	
	_delay_ms(1000);
	USART0_transmit(0xFF);
	USART0_transmit(0xFF);
	USART0_transmit(BROADCASTING_ID);
	USART0_transmit(0x04);
	USART0_transmit(0x03);
	USART0_transmit(0x03);
	USART0_transmit(0x01);
	USART0_transmit(0xF6);
	}	
	return 0;
}

