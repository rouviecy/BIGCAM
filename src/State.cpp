#include "State.h"

using namespace std;

State::State() : ComThread(){
	x = 0.;		y = 0.;		z = 0.;
	vx = 0.;	vy = 0.;	vz = 0.;
	thx = 0.;	thy = 0.;	thz = 0.;
	vthx = 0.;	vthy = 0.;	vthz = 0.;
}

void State::IO(){
	Link_output("x", &x);		Link_output("y", &y);		Link_output("z", &z);
	Link_output("vx", &vx);		Link_output("vy", &vy);		Link_output("vz", &vz);
	Link_output("thx", &thx);	Link_output("thy", &thy);	Link_output("thz", &thz);
	Link_output("vthx", &vthx);	Link_output("vthy", &vthy);	Link_output("vthz", &vthz);

	Link_input("imu_x", &imu_x);		Link_input("imu_y", &imu_y);		Link_input("imu_z", &imu_z);
	Link_input("imu_vx", &imu_vx);		Link_input("imu_vy", &imu_vy);		Link_input("imu_vz", &imu_vz);
	Link_input("imu_thx", &imu_thx);	Link_input("imu_thy", &imu_thy);	Link_input("imu_thz", &imu_thz);
	Link_input("imu_vthx", &imu_vthx);	Link_input("imu_vthy", &imu_vthy);	Link_input("imu_vthz", &imu_vthz);	

	Link_input("t", &t);
	Link_input("compas", &compas);
	Link_input("gps_x", &gps_x);
	Link_input("gps_y", &gps_y);
}

void State::Job(){
	Critical_receive();
	thz = compas;
	x = gps_x;
	y = gps_y;
	Critical_send();
}
