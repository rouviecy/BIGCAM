#include "Clock.h"

using namespace std;

Clock::Clock() : Proprioceptive(){
	start = chrono::high_resolution_clock::now();
}

void Clock::IO(){
	Link_output("t", &t);	
}

void Clock::Job(){
	now = chrono::high_resolution_clock::now();
	chrono::duration<float> delta = now - start;
	chrono::duration_cast<chrono::seconds>(delta);
	t = delta.count();
	Critical_send();
}
