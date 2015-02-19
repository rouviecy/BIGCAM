#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	if(MODE_SIMU_CAM){
		capture = cv::VideoCapture(-1);
		capture.set(CV_CAP_PROP_FRAME_WIDTH, 400);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, 300);
	}
	else{
		img_file_simu_cam = cv::imread(IMG_CAM_SIMU_PATH);
	}
	num_image = 0;
	io_file.Clear_log();
}

void Camera::IO(){
	Link_input("x", &x);
	Link_input("y", &y);
	Link_input("z", &z);
	Link_input("thz", &thz);
}

void Camera::Job(){
	struct_img message;
	message.path = "test/img";
	message.number = num_image;
	Critical_receive();
	message.x = x;
	message.y = y;
	message.z = z;
	message.thz = thz;
	if	(MODE_SIMU_CAM)	{capture >> message.img;}
	else				{message.img = Simu();}
	io_file.Write(message);
	num_image++;
}

cv::Mat Camera::Simu(){
	
}
