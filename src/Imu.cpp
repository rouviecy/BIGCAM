#include "Imu.h"

using namespace std;

Imu::Imu() : Proprioceptive(){

}

void Imu::Job(){
	for(int i = 0; i < 42; i++){
		usleep(100000);
	}
}
