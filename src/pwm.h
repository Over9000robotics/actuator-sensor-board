/**
 * @file pwm.h
 */
#ifndef PWM_H_
#define PWM_H_

#define PRESCALER_VAL 8
#define BRUSHLESS_PWM_FREQ 50 //Hz 

#define SERVO_OCR_MIN 500
#define SERVO_OCR_MAX 2500

/**
 * Sets brushless rotating speed
 * @param brushless_num - number of motor to drive, defined in actuator.h
 * @param procent - 0 -> stopped, 100 -> max rotating speed
 */
void pbr_pwm_set(uint8_t brushless_num, uint8_t procent);

void servo_pwm_set(int8_t servo_num, uint8_t degrees);


void timer1_init(void);
void timer3_init(void);

/**
 * Inits pwm pins for servo and brushless motors
 */
void pwm_init(void);

#endif
