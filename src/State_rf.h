/*
 * @(#)		State_rf.h
 * @version	1.5
 * @autor	C. Rouvière
 */

/**
 * State of the robot with serial output monitoring data
 */

#ifndef STATE_RF
#define STATE_RF

#include <cmath>
#include <cstring>
#include <iomanip>
#include <sstream>
#include "stereotypes/ComThread.h"

class State_rf : public ComThread{

public:

	State_rf();
	void Set_serial_port(int serial_port);

private:

	float	t;
	float	x,		y,		z;
	float	vx,		vy,		vz;
	float	thx,	thy,	thz;
	float	vthx,	vthy,	vthz;

	float	imu_thx,	imu_thy,	imu_thz;
	float	gps_x,		gps_y;
	float	alti;
	float	v_wind;

	int serial_port;

	void Job();
	void IO();
	void Send_serial();

};

#endif
