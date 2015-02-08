#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){
	i = 1.;
}

void Gps::IO(){
	Link_output("gps_x", &gps_x);
	Link_output("gps_y", &gps_y);
	
	Link_input("simu_gps_x", &simu_gps_x);
	Link_input("simu_gps_y", &simu_gps_y);
}

void Gps::Job(){
	Critical_receive();
	// Pretty lemniscate
	float cos1i = (float) cos(i);
	float sin1i = (float) sin(i);
	float sin2i = (float) sin(2 * i);
//	gps_x = (10. + (float) i) * cos1i / (sin1i * sin1i + 1.);
//	gps_y = (10. + (float) i) * sin2i / (sin1i * sin1i + 1.);
	gps_x = simu_gps_x;
	gps_y = simu_gps_y;
	i += 0.02;
	Critical_send();
}
