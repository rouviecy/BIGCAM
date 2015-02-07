#include "Compas.h"

using namespace std;

Compas::Compas() : Proprioceptive(){

}

void Compas::IO(){
	Link_output("compas", &compas);	
}

void Compas::Job(){
	for(int i = 0; i < 42; i++){
		usleep(100000);
		compas = i;
		Critical_send();
	}
}
