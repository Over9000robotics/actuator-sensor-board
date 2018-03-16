/**
 * @file sensor.c
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "communicator.h"
#include "sensor.h"

/******************************
* sensors[0] -> front sensor  *
* sensors[1] -> back sensor   *
******************************/

static t_sensor sensors[NUM_OF_SENS]; /** Array of sensors where sensors output data will be saved*/
static t_sensor temp[NUM_OF_SENS]; /** Temporary array of sensors data */
static uint8_t state_changed_flag = 1;

//Memristor board
// P1 -> PA0
// P2 -> PA1

/**
 * @brief Inits pin and value for sensors
 * @todo edit this function, take pin and port value as a parameter
 */
void sensors_init(void)
{
	DDRA |= (0 << PA7); //sens1 -> P1
	DDRA |= (0 << PA6); //sens2 -> P2

	sensors[0].pin = 7; //try with PA7
	sensors[1].pin = 6;

	sensors[0].value = 0;
	sensors[1].value = 0;
}

/**
 * @brief Reads states of sensor pins and edits value in sensors structure
 * If sensor active, value will be 0xFF, if not active, 0x00
 * If sensor state changed, this function will automaticaly send status
 * of all sensors to master unit via protocol defined in communicator.c
 */
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
/**
 * @brief Sends sensor status via protocol defined in communicator.c
 * packet:
 * 0xFE (start of packet)
 * sensor1.value
 * sensor2.value
 * .
 * .
 * .
 * sensorN.value 
 * 0xFC (end of packet)
 */
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
