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
	unsigned char sens = 0;	
	
	USART0_init(57600);

	//sens3  - pg2
	DDRG |= (0 << PG2);
	PORTG = 0;
	
	timer1_init();
	timer3_init();
	pwm_init();
	sensors_init();
	
	brushless_set_speed(BR_HEAD, 0);	
	brushless_set_speed(BR_SECONDARY, 0);
	
	sei();
	
	servo_pwm_set(SERVO1, 0);
	servo_pwm_set(SERVO2, 0);
	servo_pwm_set(SERVO3, 0);
	//brushless_init();
	
	while(1)
	{
		update_sensor_status();
		read_packet();
		
		send_sensor_status();
/*		
		servo_pwm_set(0, 180);
		_delay_ms(1000);
		servo_pwm_set(0, 0);
		_delay_ms(1000);
		//_delay_ms(100);
*/
	}	
	return 0;
}
