/*
 * @(#)		Pressure.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Altitude and wind sencor by I2C
 */

#ifndef PRESSURE
#define PRESSURE

#include "stereotypes/Proprioceptive.h"

class Pressure : public Proprioceptive{

public:

	Pressure();

private:

	void Job();
	void IO();

	float alti;
	float v_wind;

};

#endif
