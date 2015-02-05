#include "Servo.h"

using namespace std;

Servo::Servo() : Actuator(){
	Subscribe("/to_servo");
}

void Servo::Job(){

}
