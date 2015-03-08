/*
 * @(#)		Gps.h
 * @version	1.5
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
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Gps : public Proprioceptive{

public:

	Gps();

private:

	void Job();
	void IO();
	
	float gps_x, gps_y;
	float simu_gps_x, simu_gps_y;

	bool first;
	float offset_x, offset_y;

	#define R_EARTH 6378137.

	#ifdef MODE_RASPI
		int tty;
		char header[6];
		bool is_header;
		bool valid_msg;
		int index_header;
		std::string msg;
	#endif

	void Decode_NMEA(std::string msg_nmea);

};

#endif
