/*
 * @(#)		Remote.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Control remotely the robot in a GUI
 */

#ifndef REMOTE
#define REMOTE

#include "stereotypes/ComThread.h"

class Remote : public ComThread{

public:

	Remote();

private:

	float is_remote;
	float remote_power;
	float remote_turn;

	void Job();
	void IO();

};

#endif
