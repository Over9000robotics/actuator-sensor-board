/**
 * @file spi.h 
 */

#include <stdio.h>

#ifndef SPI_H_
#define SPI_H_

void SPI_slave_init(void);
char SPI_receive(void);
void SPI_transmit(char byte);

#endif
