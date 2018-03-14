#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <stdint.h>

#define BR_HEAD 1 		//main brushless on big the robot
#define BR_SECONDARY 2 	//secondary brushless motor on the big robot
#define NUM_OF_BRUSHLESS 2

void brushless_set_speed(uint8_t brushless_num, uint8_t procent);

#endif
