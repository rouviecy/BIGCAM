#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){

}

void Gps::IO(){
	Link_output("gps_x", &gps_x);
	Link_output("gps_y", &gps_y);
}

void Gps::Job(){
	for(int i = 0; i < 10000; i++){
		usleep(100000);
		gps_x = 1.;
		gps_y = (float) 2*i;
		Critical_send();
	}
}
