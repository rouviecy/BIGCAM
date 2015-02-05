/*
 * @(#)		Servo.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Motor control
 */

#ifndef SERVO
#define SERVO

#include "stereotypes/Actuator.h"

class Servo : public Actuator{

public:

	Servo();

private:

	void Job();

};

#endif
