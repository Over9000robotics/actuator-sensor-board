#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

void fastpwm_init(void);

int main(void)
{
	fastpwm_init();
	sei();
	
	while(1)
	{
		_delay_ms(100);
		OCR2A += 5;
		if(OCR2A > 120)
		{
			OCR2A = 0;
		}
		
		OCR1AL += 5;
		if(OCR1AL > 200)
		{
			OCR1AL = 0;
		}
		
		OCR1BL += 5;
		if(OCR1BL > 120)
		{
			OCR1BL = 0;
		}
		
		OCR1CL += 5;
		if(OCR1CL > 120)
		{
			OCR1CL = 0;
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
 ***********************************************************
 * 
 */
void fastpwm_init(void)
{
/**************OC2A********************************************/
	//fastpwm on OC2A pin
	DDRB |= (1 << PB4);
	
	TCCR2A = 0x6C;
	OCR2A = 0;
/******************************************************************/
/***************OC1A***********************************************/	
	//fast pwm on OC1A pin (PB2 - PWM2)
	DDRB |= (1 << PB5); //enable pin as output
	OCR1AH = 0;
	OCR1AL = 0;
	
	TCCR1A |= (1 << COM1A1); //clear on compare match when up counting
	TCCR1A &= ~(1 << COM1A0);
	
	//fast PWM, top = 0xFF
	TCCR1A |= (1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11); //clock select clkIO / 64 (prescaler)
	TCCR1B |= (1 << CS10);
/*********************************************************************/
/************** OC1B **************************************************/
	DDRB |= (1 << PB6);
	OCR1BH = 0;
	OCR1BL = 0;
	
	TCCR1A |= (1 << COM1B1);
	TCCR1A &= ~(1 << COM1B0);
	
/*********************************************************************/
/************* OC1C **************************************************/
	DDRB |= (1<< PB7);
	OCR1CH = 0;
	OCR1CL = 0;
	
	TCCR1A |= (1 << COM1C1);
	TCCR1A &= ~(1 << COM1C0);
	
/*********************************************************************/
/*********************************************************************/
}


