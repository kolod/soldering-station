/*
 * timer.cpp
 *
 * Created: 15.08.2022 23:04:15
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#include <xc.h>
#include <util/atomic.h>
#include "timer.h"

#define F_CPU  16000000

volatile unsigned long _millis = 0;

unsigned long millis() {
	unsigned long result;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {result = _millis;}
	return result;
}

void timer0_init() {
	// Clear registers
	TCCR0A = 0;
	TCCR0B = 0;
	TCNT0 = 0;
	
	OCR0A = 249;                     // 1000 Hz (16000000/((249+1)*64))
	TCCR0A |= _BV(WGM01);            // CTC
	TCCR0B |= _BV(CS01) | _BV(CS00); // Prescaler 64
	TIMSK0 |= _BV(OCIE0A);           // Output Compare Match A Interrupt Enable
}

ISR(TIMER0_COMPA_vect) {
	_millis++;
}
