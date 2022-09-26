/*
 * pid.h
 *
 * Created: 19.08.2022 20:07:37
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 


#pragma once

#include <stdbool.h>

typedef struct {
	float setpoint; //!< Controller setpoint
	// Tuning parameters
	float kp; //!< Stores the gain for the Proportional term
	float ki; //!< Stores the gain for the Integral term
	float kd; //!< Stores the gain for the Derivative term
	// Output minimum and maximum values
	float omin; //!< Maximum value allowed at the output
	float omax; //!< Minimum value allowed at the output
	// Variables for PID algorithm
	float iterm; //!< Accumulator for integral term
	float lastin; //!< Last input value for differential term
	// Operation mode
	bool enabled;
} pid_t;

void pid_init(pid_t* handle, float setpoint, float kp, float ki, float kd, float omin, float omax);
void pid_enable(pid_t* handle);
void pid_disable(pid_t* handle);
float pid_loop(pid_t* handle, float input);
void pid_autotune(pid_t* handle);
