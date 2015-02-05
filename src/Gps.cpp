#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){
	Subscribe("/from_gps");
}

void Gps::Job(){
	for(int i = 0; i < 42; i++){
		usleep(100000);
		Send("/from_gps", to_string(i).c_str());
	}
}
