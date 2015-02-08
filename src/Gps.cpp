#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){
	i = 1.;
}

void Gps::IO(){
	Link_output("gps_x", &gps_x);
	Link_output("gps_y", &gps_y);
}

void Gps::Job(){
	// Pretty lemniscate
	float cos1i = (float) cos(i);
	float sin1i = (float) sin(i);
	float sin2i = (float) sin(2 * i);
	gps_x = 10. * cos1i / (sin1i * sin1i + 1.);
	gps_y = 10. * sin2i / (sin1i * sin1i + 1.);
	i += 0.01;
	Critical_send();
}
