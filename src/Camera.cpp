#include "Camera.h"

using namespace std;

Camera::Camera() : Exteroceptive(){
	if(MODE_SIMU_CAM){
		img_file_simu_cam = cv::imread(IMG_CAM_SIMU_PATH);
	}
	else{
		capture = cv::VideoCapture(-1);
		capture.set(CV_CAP_PROP_FRAME_WIDTH, 400);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, 300);
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
	message.x = ADD_NOISE ? x + 0.5 * Random() : x;
	message.y = ADD_NOISE ? y + 0.5 * Random() : y;
	message.z = z;
	message.thz = ADD_NOISE ? thz + 0.1 * Random() : thz;
	if	(MODE_SIMU_CAM)	{message.img = Simu();}
	else				{capture >> message.img;}
	io_file.Write(message);
	num_image++;
}

cv::Mat Camera::Simu(){
	int pos_x = (int) (x * 10 + img_file_simu_cam.cols / 2);
	int pos_y = (int) (y * 10 + img_file_simu_cam.rows / 2);
	cv::Point position(pos_x, pos_y);
	float angle = thz * 57.296;
	return Mask::Grab_zone(img_file_simu_cam, cv::Size(200, 150), position, angle);
}

float Camera::Random(){return (float) (rand() - RAND_MAX / 2) / ((float) RAND_MAX);}
