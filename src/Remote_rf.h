/*
 * @(#)		Remote_rf.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Control remotely the robot in a GUI
 */

#ifndef REMOTE_RF
#define REMOTE_RF

#include <cstring>
#include "stereotypes/ComThread.h"

class Remote_rf : public ComThread{

public:

	Remote_rf();
	void Wait_quit_from_user();
	void Set_serial_port(int serial_port);

private:

	float switch_alive;
	float is_remote;
	float remote_power;
	float remote_turn;
	float remote_pitch;
	float remote_deriv;

	void Job();
	void IO();
	void Smooth_order();

	int serial_port;

};

#endif
