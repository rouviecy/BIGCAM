/*
 * @(#)		State.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * State of the robot
 */

#ifndef STATE
#define STATE

#include "stereotypes/ComThread.h"

class State : public ComThread{

public:

	State();

private:

	float	t;
	float	x,		y,		z;
	float	vx,		vy,		vz;
	float	thx,	thy,	thz;
	float	vthx,	vthy,	vthz;

	float	imu_x,		imu_y,		imu_z;
	float	imu_vx,		imu_vy,		imu_vz;
	float	imu_thx,	imu_thy,	imu_thz;
	float	imu_vthx,	imu_vthy,	imu_vthz;

	float	compas;
	float	gps_x,	gps_y;

	void Job();
	void IO();

};

#endif
