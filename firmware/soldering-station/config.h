/*
 * config.h
 *
 * Created: 20.08.2022 15:02:48
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#pragma once

#define ADC_CHANNEL 0

#define SEGMENT_PORT  PORTD
#define SEGMENT_DIR   DDRD
#define SEGMENT_A     0x01
#define SEGMENT_B     0x02
#define SEGMENT_C     0x04
#define SEGMENT_D     0x08
#define SEGMENT_E     0x10
#define SEGMENT_F     0x20
#define SEGMENT_G     0x40
#define SEGMENT_DP    0x80

#define COLUMN_PORT   PORTB
#define COLUMN_DIR    DDRB
#define COLUMN_1      0x01
#define COLUMN_2      0x02
#define COLUMN_3      0x04
