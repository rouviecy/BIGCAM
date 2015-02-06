#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	capture = cv::VideoCapture(-1);
	Subscribe("/odom_to_cam");
	x = 0., y = 0., z = 0;
}

void Camera::Job(){
	int i = 0;
	while(true){
		usleep(1000000);
		struct_img message;
		capture >> message.img;
		message.path = "test/img";
		message.number = i;
		if(!IsEmptyTopic("/odom_to_cam")){
			x = stof(Read("/odom_to_cam"));
		}
		message.x = x;
		message.y = y;
		message.z = z;
		io_file.Write(message);
		i++;
	}
}
