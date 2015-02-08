#include "Compas.h"

using namespace std;

Compas::Compas() : Proprioceptive(){

}

void Compas::IO(){
	Link_output("compas", &compas);
	Link_input("simu_compas", &simu_compas);	
}

void Compas::Job(){
	Critical_receive();
	compas = simu_compas;
	Critical_send();
}
