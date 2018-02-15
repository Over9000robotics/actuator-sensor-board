#ifndef AXPACKET_H_
#define AXPACKET_H_

#include <stdint.h>

#define PACKET_HEADER 5
#define MAX_PKT_SIZE 20

typedef struct t_axPacket
{
	uint8_t sync_1;
	uint8_t sync_2;
	uint8_t ax_id;
	uint8_t length; //NUM OF PARAM + 2
	uint8_t instruction;
	uint8_t parameters[MAX_PKT_SIZE-PACKET_HEADER];
	uint8_t checksum;
}t_axPacket;

void axpacket_prepare(uint8_t ax_id, uint8_t instruction);
void axpacket_put_byte(uint8_t byte);
void axpacket_put_word(uint16_t word);
void axpacket_end(void);

#endif
