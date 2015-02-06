#include "State.h"

using namespace std;

State::State() : ComThread(){
	t = 0.;
	x = 0.;		y = 0.;		z = 0.;
	vx = 0.;	vy = 0.;	vz = 0.;
	thx = 0.;	thy = 0.;	thz = 0.;
	vthx = 0.;	vthy = 0.;	vthz = 0.;
}

void State::Job(){
	while(true){
		usleep(1000000);
		s->Lock();
		thx = s->compas;
		x = s->gps_x;
		y = s->gps_y;
		s->Unlock();
		Send_state();
	}
}

void State::Send_state(){
	s->Lock();
	s->t = t;
	s->x = x;		s->y = y;		s->z = z;
	s->vx = vx;		s->vy = vy;		s->vz = vz;
	s->thx = thx;	s->thy = thy;	s->thz = thz;
	s->vthx = vthx;	s->vthy = vthy;	s->vthz = vthz;
	s->Unlock();
}
