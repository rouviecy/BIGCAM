#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	capture = cv::VideoCapture(-1);
	Subscribe("/odom_to_cam");
	coord.a = 0.; coord.b = 0.; coord.c = 0;
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
			coord = Modem::Dec_3f(Read("/odom_to_cam"));
		}
		message.x = coord.a;
		message.y = coord.b;
		message.z = coord.c;
		io_file.Write(message);
		i++;
	}
}
