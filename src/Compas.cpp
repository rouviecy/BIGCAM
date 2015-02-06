#include "Compas.h"

using namespace std;

Compas::Compas() : Proprioceptive(){

}

void Compas::Job(){
	for(int i = 0; i < 42; i++){
		usleep(100000);
		s->Lock();
		s->compas = i;
		s->Unlock();
	}
}
