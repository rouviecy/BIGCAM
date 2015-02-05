#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	capture = cv::VideoCapture(-1);
}

void Camera::Job(){
	int i = 0;
	while(true){
		usleep(1000000);
		struct_img message;
		capture >> message.img;
		message.path = "test/img";
		message.number = i;
		message.x = 42.;
		message.y = 42.;
		message.z = 42.;
		io_file.Write(message);
		i++;
	}
}
