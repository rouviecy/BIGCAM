/*
 * @(#)		Simulator.h
 * @version	1.5
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

	float x, y, thz;

	float simu_gps_x;
	float simu_gps_y;
	float simu_compas;

	float v_motor;
	float wing_left;
	float wing_right;

	void Job();
	void IO();

};

#endif
