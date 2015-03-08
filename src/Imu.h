/*
 * @(#)		Imu.h
 * @version	1.5
 * @autor	C. Rouvière
 */

/**
 * Information from IMU
 */

#ifndef IMU
#define IMU

#ifdef MODE_RASPI
	#include <wiringPi.h>
	#include <wiringSerial.h>
#endif

#include "stereotypes/Proprioceptive.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Imu : public Proprioceptive{

public:

	Imu();

private:

	void Job();
	void IO();

	float imu_thx, imu_thy, imu_thz;
	float simu_compas;

	void Decode_9DOF_RAZOR(std::string msg_ypr);

};

#endif
