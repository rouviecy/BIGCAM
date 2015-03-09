#include "Pressure.h"

using namespace std;

Pressure::Pressure() : Proprioceptive(){

}

void Pressure::IO(){
	Link_output("alti", &alti);
	Link_output("v_wind", &v_wind);
}

void Pressure::Job(){
	alti = 42;
	Critical_send();
}
