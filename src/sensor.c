#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "communicator.h"
#include "sensor.h"

/******************************
* sensors[0] -> front sensor  *
* sensors[1] -> back sensor   *
/******************************/

static t_sensor sensors[NUM_OF_SENS];
static t_sensor temp[NUM_OF_SENS];
static uint8_t state_changed_flag = 1;

//Memristor board
// P1 -> PA0
// P2 -> PA1
void sensors_init(void)
{
	DDRA |= (0 << PA7); //sens1 -> P1
	DDRA |= (0 << PA6); //sens2 -> P2

	sensors[0].pin = 0;
	sensors[1].pin = 1;

	sensors[0].value = 0;
	sensors[1].value = 0;
}

void update_sensor_status(void)
{
	temp[0].value = PINA & (1 << sensors[0].pin);
	temp[1].value = PINA & (1 << sensors[1].pin);

	if(temp[0].value > 0)
		temp[0].value = 0xFF;
	else
		temp[0].value = 0;

	if(temp[1].value > 0)
		temp[1].value = 0xFF;
	else
		temp[1].value = 0;

	int i;
	for(i = 0; i < NUM_OF_SENS; i++)
	{
		if(temp[i].value != sensors[i].value)
		{
			state_changed_flag = 1;
		}
		sensors[i].value = temp[i].value;
	}

	if(state_changed_flag)
	{
		state_changed_flag = 0;
		send_sensor_status();
	}
}

void send_sensor_status(void)
{

	transmit_byte(0xFE);

	int i;
	for(i=0; i<NUM_OF_SENS; i++)
	{
		transmit_byte(sensors[i].value);
	}

	transmit_byte(0xFC);
}
