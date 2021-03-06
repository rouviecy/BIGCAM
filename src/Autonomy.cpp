#include "Autonomy.h"

using namespace std;

Autonomy::Autonomy() : ComThread(){
	v_motor = 0.;
	stab = 0.;
	wing_left = 0.;
	wing_right = 0.;
	secu_on = false;
	t_begin_motor = 0.;
}

void Autonomy::IO(){
	Link_input("t", &t);
	Link_input("x", &x);		Link_input("y", &y);		Link_input("z", &z);
	Link_input("vx", &vx);		Link_input("vy", &vy);		Link_input("vz", &vz);
	Link_input("thx", &thx);	Link_input("thy", &thy);	Link_input("thz", &thz);
	Link_input("vthx", &vthx);	Link_input("vthy", &vthy);	Link_input("vthz", &vthz);

	Link_input("is_remote", &is_remote);
	Link_input("connection_alive", &connection_alive);
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
	// LOST CONNECTION
	if(connection_alive < 0.){
		v_motor = 0.;
		stab = 0.;
		deriv = 0.;
		wing_left = 0.;
		wing_right = 0.;
		cout << "Lost connection !" << endl;
	}
	// SEMI-AUTO
	else if(is_remote > -0.5){
		v_motor = remote_power;
		stab = remote_pitch;
		//deriv = remote_deriv;
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
		
		if(abs(remote_deriv - thz) > 0.1){
			float angle =remote_deriv - thz;
			if (angle > 0) angle = angle - 2*M_PI * ceil(angle/(2*M_PI));
			deriv = -atan(fmod(angle - M_PI, 2*M_PI) + M_PI)*2/M_PI;
		}
		
		
	}
	// FULL-AUTO
	else{
		
	}
/*	if(!secu_on && v_motor > 0.1){
		secu_on = true;
		t_begin = t;
	}
	if(secu_on){
		if(t > t_begin + 3.){
			v_motor = 0.;
		}
	}
*/	Critical_send();
}
