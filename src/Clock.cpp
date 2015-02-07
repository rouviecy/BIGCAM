#include "Clock.h"

using namespace std;

Clock::Clock() : Proprioceptive(){

}

void Clock::IO(){
	Link_output("t", &t);	
}

void Clock::Job(){
	start = chrono::high_resolution_clock::now();
	while(true){
		usleep(1000);
		now = chrono::high_resolution_clock::now();
		chrono::duration<float> delta = now - start;
		chrono::duration_cast<chrono::seconds>(delta);
		t = delta.count();
		Critical_send();
	}
}
