/**
 * @file usart0.h
 */
#include <stdio.h>

#ifndef USART0_H_
#define USART0_H_

/**
 * 
 * @brief Uart0 configuring
 * async, no parity, 1 stop bit, 8 bit data size
 * @param desired baud rate, double speed mode
 */
void USART0_init(uint32_t baud);

/**
 * @brief Uart0 transmit byte
 * @param data - byte to transmit
 */
void USART0_transmit(unsigned char data);

/**
 * @brief Uart0 read received byte
 * @return received byte
 */
unsigned char USART0_receive(void);

/*
void usart0_axpacket_send(t_axPacket* packet);
*/

#endif
