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
	Link_input("t", &t);
	Link_input("compas", &compas);
	Link_input("gps_x", &gps_x);
	Link_input("gps_y", &gps_y);
}

void State::Job(){
	while(true){
		usleep(1000000);
		Critical_receive();
		cout << t << endl;
		thx = compas;
		x = gps_x;
		y = gps_y;
		Critical_send();
	}
}
