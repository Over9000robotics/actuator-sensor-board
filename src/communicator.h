#ifndef COMMUNICATOR_H_
#define COMMUNICATOR_H_

#define CLOCK_FQ (16000000)

#define UART 1
#define SPI 2

#define BR_SET_SPEED 'B'
#define SERVO_SET_ANGLE 'A'
#define DC_ROTATE 'D'
#define CLOCKWISE 'M'
#define C_CLOCKWISE 'P'
#define DC_STOP 'H'

void transmit_byte(uint8_t byte);
uint8_t read_byte(void);
void read_packet(void);

#endif
