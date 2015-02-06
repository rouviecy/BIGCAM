#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){

}

void Gps::Job(){
	for(int i = 0; i < 42; i++){
		usleep(100000);
		s->Lock();
		s->gps_x = 1.;
		s->gps_y = 2*i;
		s->Unlock();
	}
}
