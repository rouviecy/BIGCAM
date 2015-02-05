#include "Imu.h"

using namespace std;

Imu::Imu() : Proprioceptive(){
	Subscribe("/from_imu");
}

void Imu::Job(){
	for(int i = 0; i < 42; i++){
		usleep(100000);
		Send("/from_imu", to_string(i));
	}
}
