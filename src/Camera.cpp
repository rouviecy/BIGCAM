#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	capture = cv::VideoCapture(-1);
	num_image = 0;
}

void Camera::IO(){
	Link_input("x", &x);
	Link_input("y", &y);
	Link_input("z", &z);	
}

void Camera::Job(){
	struct_img message;
	message.path = "test/img";
	message.number = num_image;
	Critical_receive();
	message.x = x;
	message.y = y;
	message.z = z;
	capture >> message.img;
	io_file.Write(message);
	num_image++;
}
