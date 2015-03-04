/*
 * @(#)		Remote.h
 * @version	1.5
 * @autor	C. Rouvière
 */

/**
 * Control remotely the robot in a GUI
 */

#ifndef REMOTE_TCP
#define REMOTE_TCP

#include <opencv2/opencv.hpp>
#include "stereotypes/ComThread.h"
#include "utils/Tcp_server.h"

class Remote_tcp : public ComThread{

public:

	Remote_tcp();
	void Wait_quit_from_user();

private:

	Tcp_server tcp_server_in;

	float is_remote;
	float remote_power;
	float remote_turn;

	void Job();
	void IO();
	void Smooth_order();

};

#endif
