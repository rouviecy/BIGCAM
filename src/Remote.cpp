#include "Remote.h"

using namespace std;

Remote::Remote() : ComThread(){
	is_remote = +1.;
	remote_power = 0.;
	remote_turn = 0.;
	pod_center = cv::Point(POD_SIZE / 2, POD_SIZE / 2);
	red =	cv::Scalar(0, 0, 255);
	blue =	cv::Scalar(255, 0, 0);
	green =	cv::Scalar(0, 255, 0);
}

void Remote::IO(){
	Link_output("is_remote", &is_remote);
	Link_output("remote_power", &remote_power);
	Link_output("remote_turn", &remote_turn);
}

void Remote::Job(){} // Do not use thread job (remember : Set_freq(-1))

void Remote::Wait_quit_from_user(){
	cv::namedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
	char key = 'a';
	while(key != 'q'){
		key = cv::waitKey(10); // ms
		if		(key == '+')	{is_remote = +1.;}
		else if (key == '-')	{is_remote = -1.;}
		else if (key == '8')	{remote_power += 0.1;}
		else if (key == '2')	{remote_power -= 0.1;}
		else if (key == '4')	{remote_turn -= 0.1;}
		else if (key == '6')	{remote_turn += 0.1;}
		Smooth_order();
		Critical_send();
		Draw_remote();
	}
	cout << "Goodbye !" << endl;
}

void Remote::Smooth_order(){
	if		(remote_power > +1.)							{remote_power = +1.;}
	else if	(remote_power < -1.)							{remote_power = -1.;}
	else if (remote_power < +0.05 && remote_power > -0.05)	{remote_power = +0.;}
	
	if		(remote_turn > +1.)		{remote_turn = +1.;}
	else if	(remote_turn < -1.)		{remote_turn = -1.;}
	else if	(remote_turn > +0.05)	{remote_turn -= 0.01;}
	else if	(remote_turn < -0.05)	{remote_turn += 0.01;}
	else							{remote_turn = 0.;}
}

void Remote::Draw_remote(){
	img_remote = cv::Mat::zeros(POD_SIZE, POD_SIZE, CV_8UC3);
	cv::line(img_remote, cv::Point(POD_SIZE / 2, - POD_SIZE), cv::Point(POD_SIZE / 2, + POD_SIZE), blue);
	cv::line(img_remote, cv::Point(- POD_SIZE, POD_SIZE / 2), cv::Point(+ POD_SIZE, POD_SIZE / 2), blue);
	int dx = + (int) (((float) POD_SIZE / 2) * remote_turn);
	int dy = - (int) (((float) POD_SIZE / 2) * remote_power);
	cv::Point pt = pod_center + cv::Point(dx, dy);
	cv::circle(img_remote, pt, 3, is_remote > 0 ? green : red, -1);
	cv::imshow(WINDOW_NAME, img_remote);
}
