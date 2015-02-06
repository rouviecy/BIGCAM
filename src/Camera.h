/*
 * @(#)		Camera.h
 * @version	1.2
 * @autor	C. Rouvière
 */

/**
 * Data from camera
 */

#ifndef CAMERA
#define CAMERA

#include <opencv2/opencv.hpp>
#include "stereotypes/Exteroceptive.h"
#include "img_proc/Io_file.h"

class Camera : public Exteroceptive{

public:

	Camera();

private:

	void Job();

	Io_file io_file;
	cv::VideoCapture capture;
	cv::Mat img_cam;

};

#endif
