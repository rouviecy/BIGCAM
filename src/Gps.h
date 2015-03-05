/*
 * @(#)		Gps.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Information from GPS
 */

#ifndef GPS
#define GPS

#ifdef MODE_RASPI
	#include <wiringPi.h>
#endif

#include "stereotypes/Proprioceptive.h"
#include <cmath>

class Gps : public Proprioceptive{

public:

	Gps();

private:

	void Job();
	void IO();
	
	float gps_x, gps_y;
	float simu_gps_x, simu_gps_y;
	
	double i;

};

#endif
