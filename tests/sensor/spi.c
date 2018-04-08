#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

/**
 * SPI Frequency: 16 000 000 / 32 = 500000
 * No interrupt
 */

void SPI_slave_init(void)
{
	DDRB |= (1<<PB3); // Set MISO output, all others input
	SPCR = (1<<SPE); // Enable SPI 
	
	SPCR |= (1 << SPR1); //fclk / 32
	SPSR |= (1 << SPI2X);
}

char SPI_receive(void)
{
	while(!(SPSR & (1<<SPIF))); // Wait for reception complete 
	
	return SPDR;
}

void SPI_transmit(char byte)
{
	SPDR = byte; // Start transmission

	while(!(SPSR & (1<<SPIF)));
}

