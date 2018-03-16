#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <stdint.h>

#define BR_HEAD 1 		//main brushless on big the robot
#define BR_SECONDARY 2 	//secondary brushless motor on the big robot

#define SERVO1 1
#define SERVO2 2
#define SERVO3 3
#define SERVO4 4

#define SERVO1_MAX 180
#define SERVO1_MIN 0

#define SERVO2_MAX 180
#define SERVO2_MIN 0

#define SERVO3_MAX 180
#define SERVO3_MIN 0

#define SERVO4_MAX 180
#define SERVO4_MIN 0

#define NUM_OF_BRUSHLESS 2
#define NUM_OF_SERVOS 5


void brushless_set_speed(uint8_t brushless_num, uint8_t procent);

void servo_set_position(int8_t servo_num, uint8_t degrees);

/**
 * Function for calibrating AeroStar brushless ESC
 */
void brushless_init(void);

uint8_t servo_limit_check(int8_t servo_num, int8_t degrees);

#endif
