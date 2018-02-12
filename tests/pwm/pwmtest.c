#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

void fastpwm_init(void);

int main(void)
{
	fastpwm_init();
	sei();
	
	DDRB = 0xFF;	
	
	while(1)
	{
		_delay_ms(100);
		OCR2A += 5;
		if(OCR2A > 120)
		{
			OCR2A = 0;
		}
	}	
	return 0;
}

/**********************************************************
 *  			OC2A pin
 * 		-TCCR2A register-
 * FOC2A  WGM20  COM2A1  COM2A0  WGM21  CS22  CS21  CS20
 *  0		1		1		0	   1	  1		0	 0
 * 
 * 
 */
void fastpwm_init(void)
{
	//fastpwm on OC2A pin
	TCCR2A = 0x6C;
	OCR2A = 0;
}
