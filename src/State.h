/*
 * @(#)		State.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * State of the robot
 */

#ifndef STATE
#define STATE

#include <cmath>
#include <iomanip>
#include <sstream>
#include "stereotypes/ComThread.h"
#include "utils/Tcp_server.h"

class State : public ComThread{

public:

	State();
	~State();

private:

	Tcp_server tcp_server_out;

	float	t;
	float	x,		y,		z;
	float	vx,		vy,		vz;
	float	thx,	thy,	thz;
	float	vthx,	vthy,	vthz;

	float	imu_thx,	imu_thy,	imu_thz;
	float	gps_x,		gps_y;
	float	alti;
	float	v_wind;

	void Job();
	void IO();

};

#endif
