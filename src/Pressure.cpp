#include "Pressure.h"

using namespace std;

Pressure::Pressure() : Proprioceptive(){
	alti = 0.;
	v_wind = 0.;
}

void Pressure::IO(){
	Link_output("alti", &alti);
	Link_output("v_wind", &v_wind);
}

void Pressure::Job(){
	alti = 42;
	v_wind = 0.;
	Critical_send();
}
