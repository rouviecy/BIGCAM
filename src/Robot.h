/*
 * @(#)		Robot.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * A robot
 */

#ifndef ROBOT
#define ROBOT

#include <vector>
#include "Autonomy.h"
#include "Camera.h"
#include "Clock.h"
#include "Compas.h"
#include "Gps.h"
#include "Imu.h"
#include "Motor.h"
#include "Remote.h"
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

	Autonomy autonomy;
	Camera camera;
	Clock clock;
	Compas compas;
	Gps gps;
	Imu imu;
	Motor motor;
	Remote remote;
	Servo servo;
	State state;

};

#endif
