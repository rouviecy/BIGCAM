#include "Motor.h"

using namespace std;

Motor::Motor() : Actuator(){
	v_motor = 0.;
}

void Motor::IO(){
	Link_input("v_motor", &v_motor);
	Link_input("wing_left", &wing_left);
	Link_input("wing_right", &wing_right);
}

void Motor::Job(){
	Critical_receive();
}
