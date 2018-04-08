#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "communicator.h"
#include "sensor.h"
#include "actuator.h"
#include "usart0.h"
#include "spi.h"

static uint8_t const selected_protocol = UART;

void transmit_byte(uint8_t byte)
{
	if(selected_protocol == UART)
	{
		USART0_transmit(byte);
	}
	else if(selected_protocol == SPI)
	{
		SPI_transmit(byte);
	}
}

uint8_t read_byte(void)
{
	uint8_t byte;
	
	if(selected_protocol == UART)
	{
		byte = USART0_receive();
	}
	
	else if(selected_protocol == SPI)
	{
		byte = SPI_receive();
	}
	
	return byte;
}

void read_packet(void)
{
	uint8_t incoming_byte = read_byte();

	switch(incoming_byte)
	{
		case SENSOR_ASK:
		{
			send_sensor_status();
			break;
		}
		case BR_SET_SPEED:
		{
			uint8_t speed = 0;
			uint8_t brushless_num = 0;
			
			brushless_num = read_byte();
			speed = read_byte();
			
			brushless_set_speed(brushless_num, speed);
			break;
		}
		
			case SERVO_SET_ANGLE:
		{
			uint8_t angle = 0;
			uint8_t servo_num = 0;
			
			servo_num = read_byte();
			angle = read_byte();
	
			servo_set_position(servo_num, angle);
			break;
		}
		
		default:
		{
			
			break;
		}
	}
}
