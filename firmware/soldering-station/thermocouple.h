/*
 * thermocouple.h
 *
 * Created: 20.08.2022 11:05:25
 *  Author: Oleksandr Kolodkin <alexandr.kolodkin@gmail.com>
 */ 

#pragma once

float voltage_to_themperature(float v) {

	const struct {
		float t0;
		float v0;
		float p1;
		float p2;
		float p3;
		float p4;
		float q1;
		float q2;
		float q3;
	} k[] = {
		{-8.7935962E+00, -3.4489914E-01,  2.5678719E+01, -4.9887904E-01, -4.4705222E-01, -4.4869203E-02,  2.3893439E-04, -2.0397750E-02, -1.8424107E-03},
		{ 3.1018976E+02,  1.2631386E+01,  2.4061949E+01,  4.0158622E+00,  2.6853917E-01, -9.7188544E-03,  1.6995872E-01,  1.1413069E-02, -3.9275155E-04},
		{ 6.0572562E+02,  2.5148718E+01,  2.3539401E+01,  4.6547228E-02,  1.3444400E-02,  5.9236853E-04,  8.3445513E-04,  4.6121445E-04,  2.5488122E-05},
	};

	const int range;

	if (v < 4.096) {
		range = 0;
	} else if (v < 16.397) {
		range = 1;
	} else {
		range = 2;
	}

	float vv0 = v - k[range].v0;
	float P = vv0 * (k[range].p1 + vv0 * (k[range].p2 + vv0 * (k[range].p3 + vv0 * k[range].p4)));
	float Q = 1 + vv0 * (k[range].q1 + vv0 * (k[range].q2 + vv0 * k[range].q3));
	
	return P / Q;
}
