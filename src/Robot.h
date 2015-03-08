/*
 * @(#)		Robot.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * A robot
 */

#ifndef ROBOT
#define ROBOT

#include <vector>
#include "utils/ComDraw.h"
#include "Altimeter.h"
#include "Autonomy.h"
#include "Camera.h"
#include "Clock.h"
#include "Gps.h"
#include "Imu.h"
#include "Motor.h"
#include "Remote_tcp.h"
#include "Servo.h"
#include "Share.h"
#include "Simulator.h"
#include "State.h"

class Robot{

public:

	Robot();

private:

	std::vector <ComThread*> threads;

	void Link_all();
	void Launch_all();
	void Join_all();

	ComDraw drawer;
	Share share;

	Altimeter	altimeter;
	Autonomy	autonomy;
	Camera		camera;
	Clock		clock;
	Gps			gps;
	Imu			imu;
	Motor		motor;
	Remote_tcp	remote_tcp;
	Servo		servo;
	Simulator	simulator;
	State		state;

};

#endif
