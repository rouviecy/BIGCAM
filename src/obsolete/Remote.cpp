#include "Remote.h"

using namespace std;

Remote::Remote() : ComThread(){
	is_remote = +1.;
	is_tcp_remote = +1.;
	remote_power = 0.;
	remote_turn = 0.;
	pod_center = cv::Point(REMOTE_SIZE / 2, REMOTE_SIZE / 2);
	red =	cv::Scalar(0, 0, 255);
	blue =	cv::Scalar(255, 0, 0);
	green =	cv::Scalar(0, 255, 0);
	img_remote = cv::Mat::zeros(REMOTE_SIZE, REMOTE_SIZE, CV_8UC3);
	cv::namedWindow(MONITOR_NAME, CV_WINDOW_AUTOSIZE);
	cv::namedWindow(REMOTE_NAME, CV_WINDOW_AUTOSIZE);
}

void Remote::IO(){
	Link_input("is_tcp_remote", &is_tcp_remote);
//	Link_output("is_remote", &is_remote);
//	Link_output("remote_power", &remote_power);
//	Link_output("remote_turn", &remote_turn);
}

void Remote::Link_images(cv::Mat img_monitor){
	this->img_monitor =	img_monitor;
}

void Remote::Job(){} // Do not use thread job (remember : Set_freq(-1))

void Remote::Wait_quit_from_user(){
	Critical_receive();
	char key = 'a';
	while(is_tcp_remote > -0.5 and key != 'q'){
		Critical_receive();
		char key = cv::waitKey(50); // ms
		if		(key == '+')	{is_remote = +1.;}
		else if (key == '-')	{is_remote = -1.;}
		else if (key == 'R')	{remote_power += 0.1;}
		else if (key == 'T')	{remote_power -= 0.1;}
		else if (key == 'Q')	{remote_turn -= 0.1;}
		else if (key == 'S')	{remote_turn += 0.1;}
//		Smooth_order();
//		Critical_send();
		Draw_remote();
	}
	cout << "Goodbye !" << endl;
	return;
}

void Remote::Smooth_order(){
	if		(remote_power > +1.)	{remote_power = +1.;}
	else if (remote_power < +0.05)	{remote_power = +0.;}
	
	if		(remote_turn > +1.)		{remote_turn = +1.;}
	else if	(remote_turn < -1.)		{remote_turn = -1.;}
	else if	(remote_turn > +0.05)	{remote_turn -= 0.01;}
	else if	(remote_turn < -0.05)	{remote_turn += 0.01;}
	else							{remote_turn = 0.;}
}

void Remote::Draw_remote(){
	img_remote = cv::Mat::zeros(REMOTE_SIZE, REMOTE_SIZE, CV_8UC3);
	cv::line(img_remote, cv::Point(REMOTE_SIZE / 2, - REMOTE_SIZE), cv::Point(REMOTE_SIZE / 2, + REMOTE_SIZE), blue);
	cv::line(img_remote, cv::Point(- REMOTE_SIZE, REMOTE_SIZE / 2), cv::Point(+ REMOTE_SIZE, REMOTE_SIZE / 2), blue);
	int dx = + (int) (((float) REMOTE_SIZE / 2) * remote_turn);
	int dy = - (int) (((float) REMOTE_SIZE / 2) * remote_power);
	cv::Point pt = pod_center + cv::Point(dx, dy);
	cv::Scalar color = is_remote > 0 ? green : red;
	cv::line(img_remote, pod_center, pt, color);
	cv::circle(img_remote, pt, 3, color, -1);
	cv::imshow(MONITOR_NAME, img_monitor);
	cv::imshow(REMOTE_NAME, img_remote);
}
