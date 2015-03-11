#include "Autonomy.h"

using namespace std;

Autonomy::Autonomy() : ComThread(){
	v_motor = 0.;
	stab = 0.;
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
	Link_output("stab", &stab);
	Link_output("wing_left", &wing_left);
	Link_output("wing_right", &wing_right);
}

void Autonomy::Job(){
	Critical_receive();
	// SEMI-AUTO
	if(is_remote > -0.5){
		v_motor = remote_power;
//		wing_left = -0.1 * remote_turn;
//		wing_right = 0.1 * remote_turn;
		stab = 0.0;
		if(thx < -0.2){
			wing_left = -1.;
			wing_right = +1.;
		}
		else if(thx > +0.2){
			wing_left = +1.;
			wing_right = -1.;
		}
		else{
			wing_left = 0.;
			wing_right = 0.;
		}
	}
	// FULL-AUTO
	else{
		
	}
	Critical_send();
}
