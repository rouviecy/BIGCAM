/*
 * @(#)		Camera.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Data from camera
 */

#ifndef CAMERA
#define CAMERA

#include <opencv2/opencv.hpp>
#include "stereotypes/Exteroceptive.h"

class Camera : public Exteroceptive{

public:

	Camera();

private:

	void Job();
	
	cv::VideoCapture capture;
	cv::Mat img_cam;

};

#endif
