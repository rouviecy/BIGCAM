/*
 * @(#)		Remote.h
 * @version	1.4
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

private:

	Tcp_server tcp_server;

	float is_remote;
	float is_tcp_remote;
	float remote_power;
	float remote_turn;

	void Job();
	void IO();
	void Smooth_order();

};

#endif