/*
 * @(#)		State.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * State of the robot
 */

#ifndef STATE
#define STATE

#include "stereotypes/ComThread.h"
#include <iostream>

class State : public ComThread{

public:

	State();

private:

	void Job();

};

#endif
