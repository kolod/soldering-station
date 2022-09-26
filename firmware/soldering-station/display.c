/*
 * display.cpp
 *
 * Created: 15.08.2022 22:57:29
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#include <xc.h>
#include "timer.h"
#include "display.h"
#include "config.h"


void display_init(display_t* handle) {
	SEGMENT_PORT = 0;
	SEGMENT_DIR = 0;
	COLUMN_PORT &= !(COLUMN_1 | COLUMN_2 | COLUMN_3);
	COLUMN_DIR |= COLUMN_1 | COLUMN_2 | COLUMN_3;
	
	handle->pos = 0;
	handle->last = millis();

	display_clear(handle);
}

void display_clear(display_t* handle) {
	for(unsigned char i=0; i<sizeof(handle->buffer); handle->buffer[i++] = 0);
}

void display_print(display_t* handle, unsigned int value) {
	if (value <= 999) {
		handle->buffer[0] = display_gliph('0' + value % 10);
		handle->buffer[1] = display_gliph('0' + value / 10 % 10);
		handle->buffer[2] = display_gliph('0' + value / 100);
	}
}

void display_loop(display_t* handle) {
	unsigned long time = millis();
	if ((time - handle->last) > 1) {
		// Get column
		handle->pos = (handle->pos + 1) % sizeof(handle->buffer);

		// Disable previous column
		COLUMN_PORT &= !(COLUMN_1 | COLUMN_2 | COLUMN_3);

		// Set char
		SEGMENT_DIR = handle->buffer[handle->pos];

		// Enable current column
		switch (handle->pos) {
			case 0: COLUMN_PORT |= COLUMN_1; break;
			case 1: COLUMN_PORT |= COLUMN_2; break;
			case 2: COLUMN_PORT |= COLUMN_3; break;
		}

		// Update last time
		handle->last = time;
	}
}

unsigned char display_gliph(char ch) {
	switch(ch) {
		case '0': return SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F;
		case '1': return SEGMENT_B | SEGMENT_C;
		case '2': return SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G;
		case '3': return SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G;
		case '4': return SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G;
		case '5': return SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G;
		case '6': return SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G;
		case '7': return SEGMENT_A | SEGMENT_B | SEGMENT_C;
		case '8': return SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G;
		case '9': return SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G;
		default: return 0;
	}
}
