#include "Monitor.h"

using namespace std;

Monitor::Monitor() : ComThread(){
	cv::namedWindow(MONITOR_NAME, CV_WINDOW_AUTOSIZE);
	red =	cv::Scalar(0, 0, 255);
	blue =	cv::Scalar(255, 0, 0);
	green =	cv::Scalar(0, 255, 0);
	x_min = -1.; x_max = +1.; y_min = -1.; y_max = +1.;
}

void Monitor::IO(){
	Link_input("x", &x);		Link_input("y", &y);		Link_input("z", &z);
	Link_input("thx", &thx);	Link_input("thy", &thy);	Link_input("thz", &thz);
}

void Monitor::Job(){
	Critical_receive();
	Draw_monitor();
}

void Monitor::Draw_monitor(){
	img_monitor = cv::Mat::zeros(MONITOR_SIZE, MONITOR_SIZE, CV_8UC3);
	cv::Point pt(x, y);
	path.push_back(pt);
	if		(x < x_min)	{x_min = x;}
	else if	(x > x_max)	{x_max = x;}
	if		(y < y_min)	{y_min = y;}
	else if	(y > y_max)	{y_max = y;}
	cv::Point pt_draw_prev;
	for(size_t i = 0; i < path.size(); i++){
		int draw_x = (int) (((float) MONITOR_SIZE) * (path[i].x - x_min) / (x_max - x_min));
		int draw_y = (int) (((float) MONITOR_SIZE) * (path[i].y - y_min) / (y_max - y_min));
		cv::Point pt_draw = cv::Point(draw_x, draw_y);
		if(i != 0){
			cv::line(img_monitor, pt_draw_prev, pt_draw, blue);
			cv::circle(img_monitor, pt_draw, 2, red, -1);
		}
		pt_draw_prev = pt_draw;
	}
	cv::imshow(MONITOR_NAME, img_monitor);
}
