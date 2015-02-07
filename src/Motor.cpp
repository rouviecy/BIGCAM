#include "Motor.h"

using namespace std;

Motor::Motor() : Actuator(){
	v_motor = 0.;
}

void Motor::IO(){
	Link_input("v_motor", &v_motor);
}

void Motor::Job(){
	while(true){
		usleep(1000000);
		Critical_receive();
	}
}
