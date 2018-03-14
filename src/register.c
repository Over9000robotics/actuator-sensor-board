#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "register.h"

void register_16_write(volatile uint16_t* adress, uint16_t value)
{
	unsigned char sreg;
	
	sreg = SREG;
	cli();
	
	*adress = value;
	
//	sei(); //delete if unnecesary
	
	SREG = sreg;
}
