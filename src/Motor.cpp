#include "Motor.h"

using namespace std;

Motor::Motor() : Actuator(){
	Subscribe("/to_motor");
}

void Motor::Job(){

}
