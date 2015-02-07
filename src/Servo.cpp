#include "Servo.h"

using namespace std;

Servo::Servo() : Actuator(){
	steer = 0.;
	wing_left = 0.;
	wing_right = 0.;
}

void Servo::IO(){
	Link_input("steer", &steer);
	Link_input("wing_left", &wing_left);
	Link_input("wing_right", &wing_right);
}

void Servo::Job(){
	Critical_receive();
}
