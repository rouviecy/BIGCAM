/*
 * @(#)		Imu.h
 * @version	1.0
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

};

#endif
