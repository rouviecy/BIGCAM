/*
 * @(#)		Servo.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Servo control (steering and wings)
 */

#ifndef SERVO
#define SERVO

#include "stereotypes/Actuator.h"

class Servo : public Actuator{

public:

	Servo();

private:

	void Job();
	void IO();

	float steer;
	float wing_left, wing_right;

};

#endif
