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
		message.path = "test/img";
		message.number = i;
		s->Lock();
		message.x = s->x;
		message.y = s->y;
		message.z = s->z;
		s->Unlock();
		capture >> message.img;
		io_file.Write(message);
		i++;
	}
}
