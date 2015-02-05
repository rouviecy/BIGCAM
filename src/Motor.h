/*
 * @(#)		Motor.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Motor control
 */

#ifndef MOTOR
#define MOTOR

#include "stereotypes/Actuator.h"

class Motor : public Actuator{

public:

	Motor();

private:

	void Job();

};

#endif
