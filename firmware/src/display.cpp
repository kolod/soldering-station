#include "display.h"
#include "config.h"

void Display::setup() {
    SEGMENT_PORT = 0;
	SEGMENT_DIR = 0;

	pinMode(COLUMN_1, OUTPUT);
	digitalWrite(COLUMN_1, LOW);
	pinMode(COLUMN_2, OUTPUT);
	digitalWrite(COLUMN_2, LOW);
	pinMode(COLUMN_3, OUTPUT);
	digitalWrite(COLUMN_3, LOW);
	
	pos = 0;
	last = millis();

	clear();
}

void Display::loop() {
    unsigned long time = millis();
	if ((time - last) > 1) {
		// Get column
		pos = (pos + 1) % sizeof(buffer);

		// Disable previous column
		digitalWrite(COLUMN_1, LOW);
		digitalWrite(COLUMN_2, LOW);
		digitalWrite(COLUMN_3, LOW);

		// Set char
		SEGMENT_DIR = buffer[pos];

		// Enable current column
		switch (pos) {
			case 0: digitalWrite(COLUMN_1, HIGH); break;
			case 1: digitalWrite(COLUMN_2, HIGH); break;
			case 2: digitalWrite(COLUMN_3, HIGH); break;
		}

		// Update last time
		last = time;
	}
}

void Display::clear() {
    for(unsigned char i=0; i<sizeof(buffer); buffer[i++] = 0);
}

void Display::print(int value) {
    if (value <= 999) {
		buffer[0] = gliph('0' + value % 10);
		buffer[1] = gliph('0' + value / 10 % 10);
		buffer[2] = gliph('0' + value / 100);
	}
}

unsigned char Display::gliph(char ch) {
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

Display display;
