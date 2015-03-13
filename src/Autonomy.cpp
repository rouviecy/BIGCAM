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
	Link_input("remote_pitch", &remote_pitch);
	Link_input("remote_deriv", &remote_deriv);

	Link_output("v_motor", &v_motor);
	Link_output("stab", &stab);
	Link_output("wing_left", &wing_left);
	Link_output("wing_right", &wing_right);
	Link_output("deriv", &deriv);
 }

void Autonomy::Job(){
	Critical_receive();
	// SEMI-AUTO
	if(is_remote > -0.5){
		v_motor = remote_power;
		stab = remote_pitch;
		deriv = remote_deriv;
		float Kp = 1./(M_PI/3.-0.2);
		if(thy < -0.2){
			wing_left = -max(-1.,Kp*(thy+0.2)-remote_turn);
			wing_right = min(1.,-Kp*(thy+0.2)+remote_turn);
		}
		else if(thy > 0.2) {
			wing_left = -min(1.,Kp*(thy-0.2)-remote_turn);
			wing_right = max(-1.,-Kp*(thy-0.2)+remote_turn);
		}
		else{
			wing_left = remote_turn;
			wing_right = remote_turn;
		}
	}
	// FULL-AUTO
	else{
		
	}
	Critical_send();
}
