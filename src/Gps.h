/*
 * @(#)		Gps.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Information from GPS
 */

#ifndef GPS
#define GPS

#include "stereotypes/Proprioceptive.h"

class Gps : public Proprioceptive{

public:

	Gps();

private:

	void Job();

};

#endif
