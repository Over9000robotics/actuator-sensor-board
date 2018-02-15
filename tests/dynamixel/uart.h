/**
 * @file uart.h
 */
#include <stdio.h>

#ifndef UART_H_
#define UART_H_

/**
 * 
 * Uart0 configuring for communication with
 * dynamixel ax-12a servo motor.
 * @param desired baud rate, double speed mode
 */
void USART0_init(unsigned int baud);


void USART0_transmit(unsigned char data);

void usart0_axpacket_send(t_axPacket* packet);
#endif
