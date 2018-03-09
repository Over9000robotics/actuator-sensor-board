#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

int main(void)
{
	sei();
	
	DDRB = 0xFF;
	//sbit(DDRB, 1);	
	
	while(1)
	{
		PORTB = 0xFF;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
	}	
	return 0;
}

