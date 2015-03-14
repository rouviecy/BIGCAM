/*
 * @(#)		Autonomy.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * State of the robot
 */

#ifndef AUTONOMY
#define AUTONOMY

#include "stereotypes/ComThread.h"
#include <cmath>

class Autonomy : public ComThread{

public:

	Autonomy();

private:

	float	t;
	float	x,		y,		z;
	float	vx,		vy,		vz;
	float	thx,	thy,	thz;
	float	vthx,	vthy,	vthz;

	float	is_remote;
	float	connection_alive;
	float	remote_power;
	float	remote_turn;
	float	remote_pitch;
	float	remote_deriv;

	float	v_motor;
	float	stab;
	float	wing_left, wing_right;
	float	deriv;

	void Job();
	void IO();

};

#endif
