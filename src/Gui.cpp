#include "Gui.h"

using namespace std;

Gui::Gui() : ComThread(){
	cv::namedWindow(MONITOR_NAME, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(REMOTE_NAME, CV_WINDOW_AUTOSIZE);
}

void Gui::IO(){}

void Gui::Link_images(cv::Mat img_remote, cv::Mat img_monitor){
	this->img_remote =	img_remote;
	this->img_monitor =	img_monitor;
}

void Gui::Job(){
	cv::imshow(MONITOR_NAME, img_monitor);
	cv::imshow(REMOTE_NAME, img_remote);
}
