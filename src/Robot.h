/*
 * @(#)		Robot.h
 * @version	1.2
 * @autor	C. Rouvière
 */

/**
 * A robot
 */

#ifndef ROBOT
#define ROBOT

#include <vector>
#include "Camera.h"
#include "Clock.h"
#include "Compas.h"
#include "Gps.h"
#include "Imu.h"
#include "Motor.h"
#include "Servo.h"
#include "Share.h"
#include "State.h"

class Robot{

public:

	Robot();

private:

	std::vector <ComThread*> threads;

	void Link_all();
	void Launch_all();
	void Join_all();

	Share share;
	State state;
	Camera camera;
	Clock clock;
	Compas compas;
	Gps gps;
	Imu imu;
	Motor motor;
	Servo servo;

};

#endif
