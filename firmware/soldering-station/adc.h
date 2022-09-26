/*
 * adc.h
 *
 * Created: 20.08.2022 11:41:33
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#pragma once

#include "config.h"

void adc_init() {
	ADMUX |= _BV(REFS0);                                          // Select Vref=AVcc
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);   // Set prescaller to 128 and enable ADC
}

void  adc_start_conversion() {
	ADMUX = (ADMUX & 0xF0) | (ADC_CHANNEL & 0x0F);
	ADCSRA |= _BV(ADSC); // single conversion mode
}

void adc_wait_conversion_done() {
	while (ADCSRA & _BV(ADSC));
}

uint16_t adc_value() {
	return ADC;
}
