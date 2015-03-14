/*
 * @(#)		Clock.h
 * @version	1.4
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
	float switch_alive;
	float connection_alive;
	float is_remote;
	float prev_switch_alive;
	float prev_t_alive;

	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point now;

};

#endif
