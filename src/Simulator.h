/*
 * @(#)		Simulator.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Simulates data for sensors with actuators' orders
 */

#ifndef SIMULATOR
#define SIMULATOR

#include <cmath>
#include "stereotypes/ComThread.h"

class Simulator : public ComThread{

public:

	Simulator();

private:

	float	x, y, thz;

	float	simu_gps_x,	simu_gps_y, simu_compas;

	float	v_motor;
	float	steer;
	float	wing_left,	wing_right;

	void Job();
	void IO();

};

#endif
