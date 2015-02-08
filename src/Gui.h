/*
 * @(#)		Gui.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Grab all images to show (in order to agregate cv::imshow calls in a only thread)
 */

#ifndef GUI
#define GUI

#include <opencv2/opencv.hpp>
#include "stereotypes/ComThread.h"

class Gui : public ComThread{

public:

	Gui();
	void Link_images(cv::Mat img_remote, cv::Mat img_monitor);

private:

	#define MONITOR_NAME	"Monitor"
	#define REMOTE_NAME		"Remote"

	void Job();
	void IO();

	cv::Mat img_remote, img_monitor;

};

#endif
