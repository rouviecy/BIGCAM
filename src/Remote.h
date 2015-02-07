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

#include <opencv2/opencv.hpp>
#include "stereotypes/ComThread.h"

class Remote : public ComThread{

public:

	Remote();
	void Wait_quit_from_user();

private:

	#define WINDOW_NAME	"Remote"
	#define POD_SIZE	100

	float is_remote;
	float remote_power;
	float remote_turn;
	
	cv::Mat img_remote;
	cv::Point pod_center;
	cv::Scalar red, blue, green;

	void Job();
	void IO();
	void Smooth_order();
	void Draw_remote();

};

#endif
