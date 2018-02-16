#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "axpacket.h"
#include "ax12.h"

#define CLOCK_FQ 16000000

void USART0_init(unsigned int baud);
void USART0_transmit(unsigned char data);

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
	
	USART0_transmit(0xFF);
	USART0_transmit(0xFF);
	USART0_transmit(0x00);
	USART0_transmit(0x07);
	USART0_transmit(0x03);
	USART0_transmit(0x1E);
	USART0_transmit(0x00);
	USART0_transmit(0x02);
	USART0_transmit(0x00);
	USART0_transmit(0x02);
	USART0_transmit(0xD3);
	
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
	}	
	return 0;
}

