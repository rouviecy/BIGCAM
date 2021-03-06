/*
 * @(#)		Camera.h
 * @version	1.5
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
#include "img_proc/Mask.h"

class Camera : public Exteroceptive{

public:

	Camera();

private:

	#define IMG_CAM_SIMU_PATH "test/simucam.jpg"

	float x, y, z, thz;
	
	int num_image;

	void Job();
	void IO();
	cv::Mat Simu();
	float Random();

	Io_file io_file;
	cv::VideoCapture capture;
	cv::Mat img_cam;
	cv::Mat img_file_simu_cam;

};

#endif
