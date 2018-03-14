/* 
 * @todo Make angle limitation for every servo
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "pwm.h"
#include "communicator.h"
#include "actuator.h"

void brushless_set_speed(uint8_t brushless_num, uint8_t procent)
{
	
	if(brushless_num > 2 || brushless_num < 0)
		return;
	
	if(procent > 100 || procent < 0)
		return;
	
	pbr_pwm_set(brushless_num, procent);
}

void servo_set_position(int8_t servo_num, int8_t degrees)
{
	if(servo_num > NUM_OF_SERVOS || servo_num < 0)
		return;
	
	if(degrees > 180 || degrees < 0)
		return;
	
	if(!servo_limit_check(servo_num, degrees))
		return;
		
	servo_pwm_set(servo_num, degrees);
}

uint8_t servo_limit_check(int8_t servo_num, int8_t degrees)
{
	uint8_t correctness = 0;
	
	if(servo_num == SERVO1)
	{
		if(degrees > SERVO1_MAX || degrees < SERVO1_MIN)
		{
			return 0;
		}
		else 
			correctness = 1;
	}
	
	else if(servo_num == SERVO2)
	{
		if(degrees > SERVO2_MAX || degrees < SERVO2_MIN)
		{
			return 0;
		}
		else 
			correctness = 1;
	}
	
	else if(servo_num == SERVO3)
	{
		if(degrees > SERVO3_MAX || degrees < SERVO3_MIN)
		{
			return 0;
		}
		else 
			correctness = 1;
	}
	
	else if(servo_num == SERVO4)
	{
		if(degrees > SERVO4_MAX || degrees < SERVO4_MIN)
		{
			return 0;
		}
		else 
			correctness = 1;
	}
	
	return correctness;
}

void brushless_init(void)
{
	pbr_pwm_set(BR_HEAD, 100);
	_delay_ms(8000);
	pbr_pwm_set(BR_HEAD, 0);
	_delay_ms(2000);
}
