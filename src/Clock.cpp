#include "Clock.h"

using namespace std;

Clock::Clock() : Proprioceptive(){
	start = chrono::high_resolution_clock::now();
	prev_switch_alive = -1.;
	prev_t_alive = 0.;
	connection_alive = +1.;
}

void Clock::IO(){
	Link_input("switch_alive", &switch_alive);
	Link_input("is_remote", &is_remote);
	Link_output("connection_alive", &connection_alive);
	Link_output("t", &t);
}

void Clock::Job(){
	Critical_receive();
	now = chrono::high_resolution_clock::now();
	chrono::duration<float> delta = now - start;
	chrono::duration_cast<chrono::seconds>(delta);
	t = delta.count();
	if(prev_switch_alive * switch_alive < 0.5){
		prev_switch_alive = switch_alive;
		prev_t_alive = t;
		connection_alive = +1.;
	}
	else if(t - prev_t_alive > 2. && is_remote > 0.5){
		connection_alive = -1.;
	}
	Critical_send();
}
