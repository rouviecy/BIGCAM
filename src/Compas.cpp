#include "Compas.h"

using namespace std;

Compas::Compas() : Proprioceptive(){

}

void Compas::IO(){
	Link_output("compas", &compas);	
}

void Compas::Job(){
	compas = 42;
	Critical_send();
}
