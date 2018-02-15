#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#define CLOCK_FQ 16000000

void USART0_init(unsigned int baud);
void USART0_transmit(unsigned char data);

int main(void)
{
	cli();
	
	USART0_init(1000000);
	
	sei();
	
	_delay_ms(1000);
	
	axpacket_prepare(1, 0x19);
	axpacket_put_byte(1);
	axpacket_end();
	
	while(1)
	{
		
	}	
	return 0;
}

