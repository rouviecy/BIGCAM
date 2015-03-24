/*
 * @(#)		CCP_Remote.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * A remote controller
 */

#ifndef CPP_REMOTE
#define CPP_REMOTE

#include <vector>
#include "utils/ComDraw.h"
#include "utils/Serial.h"
#include "Remote_Joystick.h"
#include "Share.h"

class CPP_Remote{

public:

	CPP_Remote();

private:

	std::vector <ComThread*> threads;

	void Link_all();
	void Launch_all();
	void Join_all();

	ComDraw	drawer;
	Serial	serial;
	Share	share;

	Remote_Joystick	joystick;

};

#endif
