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
	#include <wiringSerial.h>
#endif

#include "stereotypes/Proprioceptive.h"
#include <string>
#include <cmath>
#include <iostream>

class Gps : public Proprioceptive{

public:

	Gps();

private:

	void Job();
	void IO();
	
	float gps_x, gps_y;
	float simu_gps_x, simu_gps_y;

	#ifdef MODE_RASPI
		int tty;
		char header[6];
		bool is_header;
		bool valid_msg;
		int index_header;
		std::string msg;
	#endif

};

#endif
