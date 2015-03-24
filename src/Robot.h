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
#include "utils/Serial.h"
#include "Autonomy.h"
#include "Camera.h"
#include "Clock.h"
#include "Gps.h"
#include "Imu.h"
#include "Motor.h"
#include "Pressure.h"
#include "Remote_rf.h"
#include "Share.h"
#include "Simulator.h"
#include "State_rf.h"

class Robot{

public:

	Robot();

private:

	std::vector <ComThread*> threads;

	void Link_all();
	void Launch_all();
	void Join_all();

	ComDraw	drawer;
	Serial	serial;
	Share	share;

	Autonomy	autonomy;
	Camera		camera;
	Clock		clock;
	Gps			gps;
	Imu			imu;
	Motor		motor;
	Pressure	pressure;
	Remote_rf	remote_rf;
	Simulator	simulator;
	State_rf	state_rf;

};

#endif
