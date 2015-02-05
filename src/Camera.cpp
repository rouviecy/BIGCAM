#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	capture = cv::VideoCapture(-1);
}

void Camera::Job(){
	int i = 0;
	while(true){
		usleep(1000000);
		capture >> img_cam;
//		cv::imwrite("test/img" + to_string(i) + ".png", img_cam);
		i++;
	}
}
