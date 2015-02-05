#include "Compas.h"

using namespace std;

Compas::Compas() : Proprioceptive(){
	Subscribe("/from_compas");
}

void Compas::Job(){
	for(int i = 0; i < 42; i++){
		usleep(100000);
		Send("/from_compas", to_string(i));
	}
}
