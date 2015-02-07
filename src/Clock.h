/*
 * @(#)		Clock.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Track time
 */

#ifndef CLOCK
#define CLOCK

#include <chrono>
#include "stereotypes/Proprioceptive.h"

class Clock : public Proprioceptive {

public:

	Clock();

private:

	void Job();
	void IO();

	float t;
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point now;

};

#endif
