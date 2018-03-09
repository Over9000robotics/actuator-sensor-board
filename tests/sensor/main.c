#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "usart0.h"
#include "sensor.h"

#define setbit(port, bit) (port) |= (1 << (bit))
#define clearbit(port, bit) (port) &= ~(1 << (bit))

int main(void)
{
	unsigned char sens = 0;	
	
	USART0_init(57600);
	sei();

	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0x00;
	DDRA = 0x00;
	
	PORTC = 0x00;
	PORTD = 0x00;
	PORTA = 0x00;
	
	//sens3  - pg2
	DDRG |= (0 << PG2);
	PORTG = 0;
	
	sensors_init();
	//sbit(DDRB, 1);	
	
	while(1)
	{
		update_sensor_status();
		read_packet();
		
		//send_sensor_status();
		
		//_delay_ms(100);
	}	
	return 0;
}
