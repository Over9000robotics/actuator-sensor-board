#ifndef SENSOR_H_
#define SENSOR_H_

#include <stdint.h>

#define NUM_OF_SENS 2

#define SENSOR_ASK 'S'

typedef struct t_sensor
{
	uint8_t value;
	uint8_t pin;
}t_sensor;


void sensors_init(void);
void update_sensor_status(void);
void send_sensor_status(void);

#endif
