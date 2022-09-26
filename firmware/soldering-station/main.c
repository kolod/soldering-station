/*
 * main.c
 *
 * Created: 8/15/2022 10:55:06 PM
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#include <xc.h>
#include "timer.h"
#include "display.h"
#include "thermocouple.h"


display_t display;
unsigned int i = 999;

static inline void setup() {
	timer0_init();
	display_init(&display);
}

static inline void loop() {	
	i--;
	if (i > 999) i = 999;
	display_print(&display, i);
}

int main(void) {
	setup();

	unsigned long last = millis();
	unsigned long time = millis();

	for (;;) {		
		if ((time - last) > 500) {
			loop();
			last = time;
		}

		display_loop(&display);		
	}
}
