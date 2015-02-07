#include "Imu.h"

using namespace std;

Imu::Imu() : Proprioceptive(){
	imu_x = 0.;		imu_y = 0.;		imu_z = 0.;
	imu_vx = 0.;	imu_vy = 0.;	imu_vz = 0.;
	imu_thx = 0.;	imu_thy = 0.;	imu_thz = 0.;
	imu_vthx = 0.;	imu_vthy = 0.;	imu_vthz = 0.;
}

void Imu::IO(){
	Link_output("imu_x", &imu_x);		Link_output("imu_y", &imu_y);		Link_output("imu_z", &imu_z);
	Link_output("imu_vx", &imu_vx);		Link_output("imu_vy", &imu_vy);		Link_output("imu_vz", &imu_vz);
	Link_output("imu_thx", &imu_thx);	Link_output("imu_thy", &imu_thy);	Link_output("imu_thz", &imu_thz);
	Link_output("imu_vthx", &imu_vthx);	Link_output("imu_vthy", &imu_vthy);	Link_output("imu_vthz", &imu_vthz);	
}

void Imu::Job(){
	while(true){
		usleep(100000);
		Critical_send();
	}
}
