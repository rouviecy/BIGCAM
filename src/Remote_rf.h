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
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "stereotypes/ComThread.h"

class Remote_rf : public ComThread{

public:

	Remote_rf();
	~Remote_rf();
	void Wait_quit_from_user();

private:

	#define PATH_DEV_RF "/dev/serial/by-id/usb-Arduino__www.arduino.cc__Arduino_USB-Serial_A4131363239351D070E0-if00"

	float switch_alive;
	float is_remote;
	float remote_power;
	float remote_turn;
	float remote_pitch;
	float remote_deriv;

	void Job();
	void IO();
	void Smooth_order();

	int fd;
	struct termios tio_new, tio_old;

};

#endif
