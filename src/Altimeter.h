/*
 * @(#)		Altimeter.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Altitude sensor
 */

#ifndef ALTIMETER
#define ALTIMETER

#include "stereotypes/Proprioceptive.h"

class Altimeter : public Proprioceptive{

public:

	Altimeter();

private:

	void Job();
	void IO();

	float alti;

};

#endif
