#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	capture = cv::VideoCapture(-1);
	Subscribe("/odom_to_cam");
}

void Camera::Job(){
	int i = 0;
	while(true){
		usleep(1000000);
		struct_img message;
		capture >> message.img;
		message.path = "test/img";
		message.number = i;
	//	float nouvx = stof(Read("/odom_to_cam")); // TODO : vérifier si topic vide
	//	cout << "new" << nouvx << endl;
		message.x = 42.;
		message.y = 42.;
		message.z = 42.;
		io_file.Write(message);
		i++;
	}
}
