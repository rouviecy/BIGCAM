#include "State.h"

using namespace std;

State::State() : ComThread(){
	x = 0.;		y = 0.;		z = 0.;
	vx = 0.;	vy = 0.;	vz = 0.;
	thx = 0.;	thy = 0.;	thz = 0.;
	vthx = 0.;	vthy = 0.;	vthz = 0.;
	Subscribe("/from_compas");
}

void State::Job(){
	while(true){
		usleep(100000);
		string message = Read("/from_compas");
		cout << message << endl;
	}
}
