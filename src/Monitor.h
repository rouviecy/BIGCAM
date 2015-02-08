/*
 * @(#)		Monitor.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Show robot state in a GUI
 */

#ifndef MONITOR
#define MONITOR

#include <cmath>
#include <opencv2/opencv.hpp>
#include "stereotypes/ComThread.h"

class Monitor : public ComThread{

public:

	Monitor();
	cv::Mat Get_img_monitor();

private:

	#define MONITOR_SIZE	700
	#define MONITOR_BORDER	100

	float	x,		y,		z;
	float	thx,	thy,	thz;

	float	x_min,	x_max;
	float	y_min,	y_max;

	cv::Mat img_monitor;
	std::vector <std::vector <float> > path;
	cv::Scalar red, blue, green;

	void Job();
	void IO();
	void Draw_monitor();

};

#endif
