#include "Monitor.h"

using namespace std;

Monitor::Monitor() : ComThread(){
	red =	cv::Scalar(0, 0, 255);
	blue =	cv::Scalar(255, 0, 0);
	green =	cv::Scalar(0, 255, 0);
	min_coord = -1.;
	max_coord = +1.;
	img_monitor = cv::Mat::zeros(MONITOR_SIZE, MONITOR_SIZE, CV_8UC3);
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
	vector <float> xy; xy.push_back(x); xy.push_back(y); 
	path.push_back(xy);
	if		(x < min_coord)	{min_coord = x;}
	else if	(x > max_coord)	{max_coord = x;}
	if		(y < min_coord)	{min_coord = y;}
	else if	(y > max_coord)	{max_coord = y;}
	cv::Point pt_draw_prev;
	for(size_t i = 0; i < path.size(); i++){
		int draw_x = MONITOR_BORDER / 2 + (int) ((float) (MONITOR_SIZE - MONITOR_BORDER) * ((float) path[i][0] - min_coord) / (max_coord - min_coord));
		int draw_y = MONITOR_BORDER / 2 + (int) ((float) (MONITOR_SIZE - MONITOR_BORDER) * ((float) path[i][1] - min_coord) / (max_coord - min_coord));
		cv::Point pt_draw = cv::Point(draw_x, draw_y);
		if(i != 0){
			cv::line(img_monitor, pt_draw_prev, pt_draw, blue);
		}
		pt_draw_prev = pt_draw;
		if(i == path.size() - 1){
			cv::circle(img_monitor, pt_draw, 10, red, 3);
			cv::Point pt_arrow = pt_draw + cv::Point(40 * cos(thz), 40 * sin(thz));
			cv::Point pt_arrow_l = pt_arrow + cv::Point(10 * cos(thz + 2.5), 10 * sin(thz + 2.5));
			cv::Point pt_arrow_r = pt_arrow + cv::Point(10 * cos(thz - 2.5), 10 * sin(thz - 2.5));
			cv::line(img_monitor, pt_draw, pt_arrow, red, 3);
			cv::line(img_monitor, pt_arrow, pt_arrow_l, red, 3);
			cv::line(img_monitor, pt_arrow, pt_arrow_r, red, 3);
		}
	}
	string text_x = "x = " + to_string(x);
	string text_y = "y = " + to_string(y);
	string text_z = "z = " + to_string(z);
	cv::putText(img_monitor, text_x, cv::Point(10, 20), CV_FONT_HERSHEY_SIMPLEX, 0.5, red);
	cv::putText(img_monitor, text_y, cv::Point(10, 40), CV_FONT_HERSHEY_SIMPLEX, 0.5, red);
	cv::putText(img_monitor, text_z, cv::Point(10, 60), CV_FONT_HERSHEY_SIMPLEX, 0.5, red);
}

cv::Mat Monitor::Get_img_monitor(){return img_monitor;}
