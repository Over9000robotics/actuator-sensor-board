#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "usart0.h"
#include "sensor.h"
#include "actuator.h"
#include "communicator.h"
#include "pwm.h"

#define setbit(port, bit) (port) |= (1 << (bit))
#define clearbit(port, bit) (port) &= ~(1 << (bit))

int main(void)
{
	unsigned char sens = 0;	
	
	USART0_init(57600);

	//sens3  - pg2
	DDRG |= (0 << PG2);
	PORTG = 0;
	
	pwm_init();
	sensors_init();
	
	brushless_set_speed(BR_HEAD, 0);	
	brushless_set_speed(BR_SECONDARY, 0);
	
	sei();
	
	//brushless_init();
	
	while(1)
	{
		update_sensor_status();
		read_packet();
		
		send_sensor_status();
		
		//_delay_ms(100);
	}	
	return 0;
}
