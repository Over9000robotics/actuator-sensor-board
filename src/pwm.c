/**
 * @file pwm.c
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "pwm.h"
#include "actuator.h"
#include "communicator.h"
#include "register.h"


volatile static uint16_t* servo1 = &OCR1A; //PB2 connector
volatile static uint16_t* servo2 = &OCR1B; //PB3 connector
volatile static uint16_t* servo3 = &OCR1C; //PB4 connector

/********************************************************************
 * @note PWM on 8-bit timer2 not implemented						*
 * On our robot, there would be three pwm servos					*
 * Fourth pwm connector could be universal for some backup systems  *
 ********************************************************************/
volatile static  uint8_t* servo4 = &OCR2A; //PB1 connector

volatile static uint16_t* head_brushless = &OCR3C;	 //PBR1
volatile static uint16_t* second_brushless = &OCR3B; //PBR2

static uint32_t icr3_temp;
static uint32_t icr1_temp;

/**
 * @brief Sets duty cycle on desired brushless
 * @param brushless_num - number of motor to give duty cycle
 * @param procent - 0 % - 100 % of duty cycle
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

	//pwm_val = (int) ((icr3_temp * procent) / 100); //test -> pwm can be from 0 to max pwm period

	pwm_val = 1000 + procent * (1000 / 100);

	if(brushless_num == BR_HEAD)
	{
		register_16_write(head_brushless, pwm_val);
	}

	else if(brushless_num == BR_SECONDARY)
	{
		register_16_write(second_brushless, pwm_val);
	}
}

/**
 * @brief Sets duty cycle of pwm servo
 * @param servo_num - number of desired servo
 * @param degrees - angle to go, it can be restricted with
 * MAX and MIN parameters defined in actuator.h
 * 
 * Pusle width -> 20 ms
 * Duty cycle -> 0.5 to 2.5 ms
 */
void servo_pwm_set(int8_t servo_num, uint8_t degrees)
{
	uint32_t pwm_val = 0;

	//	16-bit pwm timers
	// 500  -> 0.5 ms -> position LEFT
	// 1500 -> 1.5 ms -> position RIGHT
	
	pwm_val = SERVO_OCR_MIN + ((uint32_t) degrees * (SERVO_OCR_MAX-SERVO_OCR_MIN)) / 180;
	
	if(servo_num == SERVO1)
		register_16_write(servo1, pwm_val);
	
	else if(servo_num == SERVO2)
		register_16_write(servo2, pwm_val);
	
	else if(servo_num == SERVO3)
		register_16_write(servo3, pwm_val);
/*
	else if(servo_num == SERVO4)
		pwm_val = 
		*servo4 = pwm_val
*/
}

/**
 * Initialisation for 16-bit Timer1
 */
void timer1_init(void)
{
	//Phase correct mode
	icr1_temp = CLOCK_FQ / (2 * PRESCALER_VAL * SERVO_PWM_FREQ);

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13);
	TCCR1B |= (1 << CS11); //prescaler = 8

	register_16_write(&ICR1, icr1_temp);
	//ICR1H = icr1_temp >> 8;
	//ICR1L = icr1_temp;
}

/**
 * Initialisation for 16-bit Timer3
 */
void timer3_init(void)
{
	//Phase correct mode, timer 3
	icr3_temp = CLOCK_FQ / (2 * PRESCALER_VAL * BRUSHLESS_PWM_FREQ);

	TCCR3A |= (1 << WGM31);
	TCCR3B |= (1 << WGM33);
	TCCR3B |= (1 << CS31); //prescaler = 8

	register_16_write(&ICR3, icr3_temp);
	//ICR3H = icr3_temp >> 8;
	//ICR3L = icr3_temp;
}


void pwm_init(void)
{

	//fastpwm on OC2A pin
	DDRB |= (1 << PB4);

	TCCR2A = 0x6C;
	OCR2A = 0;

/***************OC1A******/
	//fast pwm on OC1A pin (PB2 - PWM2)
	DDRB |= (1 << PB5); //enable pin as output
	OCR1AH = 0;
	OCR1AL = 0;

//	TCCR1A |= (1 << COM1A1); //clear on compare match when up counting
//	TCCR1A &= ~(1 << COM1A0);
	TCCR1A |= (1 << COM1A1);

/************** OC1B ******/
	DDRB |= (1 << PB6);
	OCR1BH = 0;
	OCR1BL = 0;

	TCCR1A |= (1 << COM1B1);
//	TCCR1A |= (1 << COM1B1);
//	TCCR1A &= ~(1 << COM1B0);

/************* OC1C ********/
	DDRB |= (1 << PB7);
	OCR1CH = 0;
	OCR1CL = 0;

	TCCR1A |= (1 << COM1C1);
//	TCCR1A |= (1 << COM1C1);
//	TCCR1A &= ~(1 << COM1C0);

/*********OC3C - PBR1********/
//OC3C
	DDRE |= (1 << PE5);
	TCCR3A |= (1 << COM3C1);

	OCR3CH = 0;
	OCR3CL = 0;
	
/********OC3B - PBR2**********/
	DDRE |= (1 << PE4);
	TCCR3A |= (1 << COM3B1);

	OCR3BH = 0;
	OCR3BL = 0;
}
