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

	#define DEG_TO_RAD 0.0174533

	#ifdef MODE_RASPI
		int tty;
		char header[5];
		bool is_header;
		bool valid_msg;
		int index_header;
		std::string msg;
	#endif

	void Decode_9DOF_RAZOR(std::string msg_ypr);

};

#endif
