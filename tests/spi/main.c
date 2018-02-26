#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "usart0.h"
#include "spi.h"

int main(void)
{
	USART0_init(57600);
	SPI_SlaveInit();
	DDRB = 0xFF;
	unsigned char received_byte = 0;
	
	while(1)
	{
		received_byte = SPI_SlaveReceive();
		USART0_transmit(received_byte);
		_delay_ms(500);
	}
	
	return 0;
}
