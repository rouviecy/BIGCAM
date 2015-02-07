#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	capture = cv::VideoCapture(-1);

}

void Camera::IO(){
	Link_input("x", &x);
	Link_input("y", &y);
	Link_input("z", &z);	
}

void Camera::Job(){
	int i = 0;
	while(true){
		usleep(1000000);
		struct_img message;
		message.path = "test/img";
		message.number = i;
		Critical_receive();
		message.x = x;
		message.y = y;
		message.z = z;
		capture >> message.img;
		io_file.Write(message);
		i++;
	}
}
