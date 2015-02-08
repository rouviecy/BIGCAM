/*
 * @(#)		Imu.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Information from IMU
 */

#ifndef IMU
#define IMU

#include "stereotypes/Proprioceptive.h"

class Imu : public Proprioceptive{

public:

	Imu();

private:

	void Job();
	void IO();

	float imu_x,	imu_y,		imu_z;
	float imu_vx,	imu_vy,		imu_vz;
	float imu_thx,	imu_thy,	imu_thz;
	float imu_vthx,	imu_vthy,	imu_vthz;

};

#endif
