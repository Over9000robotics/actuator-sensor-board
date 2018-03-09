#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "communicator.h"
#include "sensor.h"
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
		
		default:
		{
			break;
		}
	}
}
