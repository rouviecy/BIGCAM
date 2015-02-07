#include "Autonomy.h"

using namespace std;

Autonomy::Autonomy() : ComThread(){

}

void Autonomy::IO(){
	Link_input("t", &t);
	Link_input("x", &x);		Link_input("y", &y);		Link_input("z", &z);
	Link_input("vx", &vx);		Link_input("vy", &vy);		Link_input("vz", &vz);
	Link_input("thx", &thx);	Link_input("thy", &thy);	Link_input("thz", &thz);
	Link_input("vthx", &vthx);	Link_input("vthy", &vthy);	Link_input("vthz", &vthz);

	Link_output("v_motor", &v_motor);
	Link_output("steer", &steer);
	Link_output("wing_left", &wing_left);
	Link_output("wing_right", &wing_right);
}

void Autonomy::Job(){
	while(true){
		usleep(1000000);
		Critical_receive();

		Critical_send();
	}
}