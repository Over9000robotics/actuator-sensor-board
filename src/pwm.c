#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "pwm.h"
#include "actuator.h"
#include "communicator.h"

static uint32_t icr_temp;

/*
int main(void)
{
	char up_down = 1;
	pwm_init();
	sei();
	uint16_t pbr1_test = 0;
	//brushless_init();
	
	while(1)
	{
		
		_delay_ms(500);
		
		if(up_down)
		{
			OCR2A += 20;
		}
		else
		{
			OCR2A -= 20;
		}
		
		if(OCR2A > 200)
		{
			up_down = 0;
		}
		if(OCR2A < 0)
		{
			up_down = 1;
		}
		
		OCR1AL += 5;
		if(OCR1AL > 200)
		{
			OCR1AL = 0;
		}
		
		OCR1BL += 5;
		if(OCR1BL > 200)
		{
			OCR1BL = 0;
		}
		
		OCR1CL += 5;
		if(OCR1CL > 200)
		{
			OCR1CL = 0;
		}
	
		pbr1_test+= 2;
		if(pbr1_test > 100)
			pbr1_test = 0;
		pbr1_pwm_set(0);
	}	
	return 0;
}
*/

/**
 * min -> 1 ms -> pwm = 1000
 * max -> 2 ms -> pwm = 2000
 * -> offset = 1000
 * 0% - 100% will be from 1000 to 2000 
*/
void pbr_pwm_set(uint8_t brushless_num, uint8_t procent)
{
	uint32_t pwm_val = 0;
	
	if(procent > 100 || procent < 0)
		return;
	
	
	//pwm_val = (int) ((icr_temp * procent) / 100); //test -> pwm can be from 0 to max
	
	pwm_val = 1000 + procent * (1000 / 100);
	
	if(brushless_num == BR_HEAD)
	{
		OCR3CH = pwm_val >> 8;
		OCR3CL = pwm_val;
	}
	
	else if(brushless_num == BR_SECONDARY)
	{
		OCR3BH = pwm_val >> 8;
		OCR3BL = pwm_val;
	}
	
	//pwm_val = (int) ((icr_temp * procent) / 100);
/*	
	pwm_val = 1000 + procent * (1000 / 100);
	
	OCR3CH = pwm_val >> 8;
	OCR3CL = pwm_val;
*/
}


void brushless_init()
{
	pbr_pwm_set(BR_HEAD, 100);
	_delay_ms(8000);
	pbr_pwm_set(BR_HEAD, 0);
	_delay_ms(2000);
}

void pwm_init(void)
{
	
/**********************************************************
 *  			OC2A pin
 * 		-TCCR2A register-
 * FOC2A  WGM20  COM2A1  COM2A0  WGM21  CS22  CS21  CS20
 *  0		1		1		0	   1	  1		0	 0
 * 
 **********************************************************/
	//fastpwm on OC2A pin
	DDRB |= (1 << PB4);
	
	TCCR2A = 0x6C;
	OCR2A = 0;
/******************************************************************/

	//Timer 1
	//fast PWM, top = 0xFF
	
	TCCR1A |= (1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11); //clock select clkIO / 64 (prescaler)
	TCCR1B |= (1 << CS10);
	
/***************OC1A***********************************************/	
	//fast pwm on OC1A pin (PB2 - PWM2)
	DDRB |= (1 << PB5); //enable pin as output
	OCR1AH = 0;
	OCR1AL = 0;
	
	TCCR1A |= (1 << COM1A1); //clear on compare match when up counting
	TCCR1A &= ~(1 << COM1A0);
	
/*********************************************************************/
/************** OC1B **************************************************/
	DDRB |= (1 << PB6);
	OCR1BH = 0;
	OCR1BL = 0;
	
	TCCR1A |= (1 << COM1B1);
	TCCR1A &= ~(1 << COM1B0);
	
/*********************************************************************/
/************* OC1C **************************************************/
	DDRB |= (1 << PB7);
	OCR1CH = 0;
	OCR1CL = 0;
	
	TCCR1A |= (1 << COM1C1);
	TCCR1A &= ~(1 << COM1C0);
	
/*********************************************************************/

//Phase correct mode, timer 3
	
	icr_temp = CLOCK_FQ / (2 * PRESCALER_VAL * BRUSHLESS_PWM_FREQ);
	
	TCCR3A |= (1 << WGM31);
	TCCR3B |= (1 << WGM33);
	TCCR3B |= (1 << CS31); //prescaler = 8
	
	//icr_temp = 20000; //override calculation
		
	ICR3H = icr_temp >> 8;
	ICR3L = icr_temp;
/*********OC3C - PBR1*************************************************/
//OC3C
	DDRE |= (1 << PE5);
	TCCR3A |= (1 << COM3C1); 
	
	OCR3CH = 0;
	OCR3CL = 0;
/********OC3B - PBR2**************************************************/
	DDRE |= (1 << PE4);
	TCCR3A |= (1 << COM3B1);
	
	OCR3BH = 0;
	OCR3BL = 0;
}


