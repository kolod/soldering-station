/*
 * display.h
 *
 * Created: 15.08.2022 22:57:47
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#pragma once

typedef struct {
	unsigned char pos;
	unsigned char buffer[3];
	unsigned long last;
} display_t;

void display_init(display_t* handle);
void display_clear(display_t* handle);
void display_print(display_t* handle, unsigned int value);
void display_loop(display_t* handle);
unsigned char display_gliph(char ch);
