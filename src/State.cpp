#include "State.h"

using namespace std;

State::State() : ComThread(){
	x = 0.;		y = 0.;		z = 0.;
	vx = 0.;	vy = 0.;	vz = 0.;
	thx = 0.;	thy = 0.;	thz = 0.;
	vthx = 0.;	vthy = 0.;	vthz = 0.;
	tcp_server_out.Configure(TCP_PORT_OUT);
}

State::~State(){
	tcp_server_out.Send("bye");
	usleep(10000);
	tcp_server_out.Close();
}

void State::IO(){
	Link_output("x", &x);		Link_output("y", &y);		Link_output("z", &z);
	Link_output("vx", &vx);		Link_output("vy", &vy);		Link_output("vz", &vz);
	Link_output("thx", &thx);	Link_output("thy", &thy);	Link_output("thz", &thz);
	Link_output("vthx", &vthx);	Link_output("vthy", &vthy);	Link_output("vthz", &vthz);

	Link_input("t", &t);
	Link_input("alti", &alti);
	Link_input("gps_x", &gps_x);
	Link_input("gps_y", &gps_y);
	Link_input("imu_thx", &imu_thx);
	Link_input("imu_thy", &imu_thy);
	Link_input("imu_thz", &imu_thz);
}

void State::Job(){
	Critical_receive();
	z = alti;
	thz = imu_thz;
	if(thz < -10 or thz > +10){thz -= floor(thz / 6.2832) * 6.2832;}
	x = gps_x;
	y = gps_y;
	ostringstream ss;
	ss << setprecision(8) << x << "|" << setprecision(8) << y << "|" << setprecision(8) << z << "|" << setprecision(8) << thz << "|";
	tcp_server_out.Send(ss.str());
	Critical_send();
}
