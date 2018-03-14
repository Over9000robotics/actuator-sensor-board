#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "pwm.h"
#include "communicator.h"
#include "actuator.h"

static uint8_t* head_brushless = &OCR3CH;
static uint8_t* second_brushless = &OCR3AH;

void brushless_set_speed(uint8_t brushless_num, uint8_t procent)
{
	
	if(brushless_num > 2 || brushless_num < 0)
		return;
	
	if(procent > 100 || procent < 0)
		return;
	
	pbr_pwm_set(brushless_num, procent);
}

