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
	float	remote_power;
	float	remote_turn;

	float	v_motor;
	float	steer;
	float	wing_left, wing_right;

	void Job();
	void IO();

};

#endif
