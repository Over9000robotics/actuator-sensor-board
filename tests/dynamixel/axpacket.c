#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "axpacket.h"
#include "uart.h"

static t_axPacket tx_packet;

void axpacket_prepare(uint8_t ax_id, uint8_t instruction)
{
	tx_packet.ax_id = ax_id;
	tx_packet.instruction = instruction;
	tx_packet.length = 0;
}

void axpacket_put_byte(uint8_t byte)
{
	tx_packet.parameters[tx_packet.length++] = byte;
}

void axpacket_put_word(uint16_t word)
{
	tx_packet.parameters[tx_packet.length++] = word >> 8;
	tx_packet.parameters[tx_packet.length++] = (uint8_t) word;
}

void axpacket_end(void)
{
	uint16_t checksum;
	
	tx_packet.length += 2; //num of parameters + 2
	
	//calculate checksum
	checksum = tx_packet.ax_id + tx_packet.length + tx_packet.instruction;
	
	int i;
	for(i=0; i<tx_packet.length-2; i++)
	{
		checksum += tx_packet.parameters[i];
	}
	
	tx_packet.checksum = ~(checksum);
	
	usart0_axpacket_send(&tx_packet);
}
