/**
 * @file main.c
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "usart0.h"
#include "sensor.h"
#include "actuator.h"
#include "communicator.h"
#include "pwm.h"
#include "register.h"

int main(void)
{
	USART0_init(57600);

	timer1_init();
	timer3_init();
	pwm_init();
	sensors_init();
	
//	brushless_set_speed(BR_HEAD, 0);	
//	brushless_set_speed(BR_SECONDARY, 0);
	
	sei();
	
//	servo_pwm_set(SERVO1,180);
//	_delay_ms(4000);
//	servo_pwm_set(SERVO1,0);
//	servo_pwm_set(SERVO2, 180);
//	servo_pwm_set(SERVO3, 180);
	//brushless_init();
	
	while(1)
	{
		update_sensor_status();
		read_packet();
		
		send_sensor_status();
	}	
	return 0;
}
