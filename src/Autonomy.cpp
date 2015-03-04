#include "Autonomy.h"

using namespace std;

Autonomy::Autonomy() : ComThread(){
	v_motor = 0.;
	steer = 0.;
	wing_left = 0.;
	wing_right = 0.;
}

void Autonomy::IO(){
	Link_input("t", &t);
	Link_input("x", &x);		Link_input("y", &y);		Link_input("z", &z);
	Link_input("vx", &vx);		Link_input("vy", &vy);		Link_input("vz", &vz);
	Link_input("thx", &thx);	Link_input("thy", &thy);	Link_input("thz", &thz);
	Link_input("vthx", &vthx);	Link_input("vthy", &vthy);	Link_input("vthz", &vthz);

	Link_input("is_remote", &is_remote);
	Link_input("remote_power", &remote_power);
	Link_input("remote_turn", &remote_turn);

	Link_output("v_motor", &v_motor);
	Link_output("steer", &steer);
	Link_output("wing_left", &wing_left);
	Link_output("wing_right", &wing_right);
}

void Autonomy::Job(){
	Critical_receive();
	if(is_remote > 0){
		v_motor = remote_power;
		steer = 0.1 * remote_turn;
		wing_left = -0.1 * remote_turn;
		wing_right = 0.1 * remote_turn;
	}
	Critical_send();
}
