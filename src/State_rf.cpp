#include "State_rf.h"

using namespace std;

State_rf::State_rf() : ComThread(){
	x = 0.;		y = 0.;		z = 0.;
	vx = 0.;	vy = 0.;	vz = 0.;
	thx = 0.;	thy = 0.;	thz = 0.;
	vthx = 0.;	vthy = 0.;	vthz = 0.;
}

void State_rf::IO(){
	Link_output("x", &x);		Link_output("y", &y);		Link_output("z", &z);
	Link_output("vx", &vx);		Link_output("vy", &vy);		Link_output("vz", &vz);
	Link_output("thx", &thx);	Link_output("thy", &thy);	Link_output("thz", &thz);
	Link_output("vthx", &vthx);	Link_output("vthy", &vthy);	Link_output("vthz", &vthz);

	Link_input("t", &t);
	Link_input("alti", &alti);
	Link_input("v_wind", &v_wind);
	Link_input("gps_x", &gps_x);
	Link_input("gps_y", &gps_y);
	Link_input("imu_thx", &imu_thx);
	Link_input("imu_thy", &imu_thy);
	Link_input("imu_thz", &imu_thz);
}

void State_rf::Job(){
	Critical_receive();
	z = alti;
	thx = imu_thx;
	thy = imu_thy;
	thz = imu_thz;
	if(thz < -10 or thz > +10){thz -= floor(thz / 6.2832) * 6.2832;}
	x = gps_x;
	y = gps_y;
	Send_serial();
	Critical_send();
}

void State_rf::Send_serial(){
	ostringstream ss;
	ss	<< setprecision(8) << x << "@"
		<< setprecision(8) << y << "@"
		<< setprecision(8) << z << "@"
		<< setprecision(8) << thz << "@\r\n";
	char msg[1024];
	strncpy(msg, ss.str().c_str(), sizeof(msg));
	msg[sizeof(msg) - 1] = '\0';
	write(serial_port, msg, 1024);
}

void State_rf::Set_serial_port(int serial_port){this->serial_port = serial_port;}
