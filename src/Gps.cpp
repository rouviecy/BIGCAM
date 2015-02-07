#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){

}

void Gps::IO(){
	Link_output("gps_x", &gps_x);
	Link_output("gps_y", &gps_y);
}

void Gps::Job(){
	gps_x = 1.;
	gps_y = (float) 2*42;
	Critical_send();
}
