/*
 * @(#)		Motor.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Motor and servo-motors control by PWM
 */

#ifndef MOTOR
#define MOTOR

#ifdef MODE_RASPI
	#include <wiringPi.h>
	#include <softPwm.h>
#endif

#include "stereotypes/Actuator.h"

class Motor : public Actuator{

public:

	Motor();

private:

	void Job();
	void IO();

	float v_motor;
	float wing_left;
	float wing_right;

	#define GPIO_MOTOR		17
	#define GPIO_SERVO_L	27
	#define GPIO_SERVO_R	22

};

#endif
