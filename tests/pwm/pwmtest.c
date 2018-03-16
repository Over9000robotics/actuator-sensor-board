#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CLKK 16000000
#define PRESCALER_VAL 8
#define BRUSHLESS_PWM_FREQ 50 //Hz 

static uint32_t icr_temp = 0;

void fastpwm_init(void);
void pbr1_pwm_set(uint16_t procent);
void brushless_init();

int main(void)
{
	uint8_t* PB1_PWM =  &OCR2A;
	char up_down = 1;
	fastpwm_init();
	sei();
	uint16_t pbr1_test = 0;
	//brushless_init();
	
	while(1)
	{
		_delay_ms(50);
		
		if(up_down)
		{
			*PB1_PWM += 20;
		}
		else
		{
			*PB1_PWM -= 20;
		}
		
		if(*PB1_PWM > 200)
		{
			up_down = 0;
		}
		if(*PB1_PWM < 0)
		{
			up_down = 1;
		}
/*		
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
		* **/
	}	
	return 0;
}

// min -> 1 ms -> pwm = 1000
// max -> 2 ms -> pwm = 2000
// prema tome, offset = 1000
// 0% - 100% ce biti raspon 1000 do 2000
void pbr1_pwm_set(uint16_t procent)
{
	if(procent > 100 || procent < 0)
		return;
	
	uint32_t pwm_val = 0;
	
	//pwm_val = (int) ((icr_temp * procent) / 100);
	
	pwm_val = 1000 + procent * (1000 / 100);
	
	OCR3CH = pwm_val >> 8;
	OCR3CL = pwm_val;
}

void brushless_init()
{
	pbr1_pwm_set(100);
	_delay_ms(8000);
	pbr1_pwm_set(0);
	_delay_ms(2000);
	//pbr1_pwm_set(10);
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
	DDRB |= (1 << PB7);
	OCR1CH = 0;
	OCR1CL = 0;
	
	TCCR1A |= (1 << COM1C1);
	TCCR1A &= ~(1 << COM1C0);
	
/*********************************************************************/

//Phase correct mode, timer 3
	
	icr_temp = F_CLKK / (2 * PRESCALER_VAL * BRUSHLESS_PWM_FREQ);
	
	TCCR3A |= (1 << WGM31);
	TCCR3B |= (1 << WGM33);
	TCCR3B |= (1 << CS31); //prescaler = 8
	
	//icr_temp = 20000; //override calculation
	
/*********OC3C - PBR1*************************************************/
//OC3C
	DDRE |= (1 << PE5);
	TCCR3A |= (1 << COM3C1); 
	ICR3H = icr_temp >> 8;
	ICR3L = icr_temp;
	
	OCR3CH = 0;
	OCR3CL = 0;
/*********************************************************************/
	DDRE |= (1 << PE4);
	TCCR3A |= (1 << COM3B1);
}


