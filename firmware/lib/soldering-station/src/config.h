/*
 * config.h
 *
 * Created: 20.08.2022 15:02:48
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#pragma once

#ifdef UNIT_TEST
    #include "ArduinoFake.h"
    extern volatile unsigned char PORTD;
    extern volatile unsigned char DDRD;
#else
    #include "Arduino.h"
#endif

#define ADC_CHANNEL 0

#define SEGMENT_PORT  PORTD
#define SEGMENT_DIR   DDRD
#define SEGMENT_A     0x20
#define SEGMENT_B     0x80
#define SEGMENT_C     0x02
#define SEGMENT_D     0x08
#define SEGMENT_E     0x10
#define SEGMENT_F     0x40
#define SEGMENT_G     0x01
#define SEGMENT_DP    0x04

#define COLUMN_1      8
#define COLUMN_2      18
#define COLUMN_3      17

#define BUZZER        10

#define ENCODER_A     15
#define ENCODER_B     16
#define ENCODER_KEY   14
