/*
 * pid.c
 *
 * Created: 19.08.2022 20:07:25
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#include "pid.h"

static inline float bound(float value, float min, float max) {
	if (value > max) return max;
	if (value < min) return min;
	return value;
}

void pid_init(pid_t* handle, float setpoint, float kp, float ki, float kd, float omin, float omax) {
	handle->setpoint = setpoint;
	handle->kp = kp;
	handle->ki = ki;
	handle->kd = kd;
	handle->omin = omin;
	handle->omax = omax;
	handle->enabled = false;
}

void pid_enable(pid_t* handle) {
	handle->enabled = true;	
}

void pid_disable(pid_t* handle) {
	handle->enabled = false;
}

float pid_loop(pid_t* handle, float input) {
	if (handle->enabled == false) return 0;

	float error = handle->setpoint - input;  // Error	
	handle->iterm = handle->iterm + error; // Compute integral	

	float P = handle->kp * error;
	float I = handle->ki * handle->iterm;
	float D = handle->kd * (handle->lastin - input);
	float result = P + I + D; 

	handle->lastin = input;
	return bound(result, handle->omin, handle->omax);
}

void pid_autotune(pid_t* handle) {
	;
}