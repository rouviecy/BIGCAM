#include "ComThread.h"

using namespace std;

ComThread::ComThread(){
	
}

void ComThread::Link(Share *s){
	this->s = s;
	IO();
}

void ComThread::Launch(){
	thr = thread(&ComThread::Job, this);
}

void ComThread::Join(){
	thr.join();
}

void ComThread::Link_input(string key, float *p_float){
	critical_input[key] = p_float;
	s->Create_data(key);
}

void ComThread::Link_output(string key, float *p_float){
	critical_output[key] = p_float;
	s->Create_data(key);
}

void ComThread::Critical_receive(){
	StringVec keys;
	for(PFloatMap::iterator it = critical_input.begin(); it != critical_input.end(); ++it){
		keys.push_back(it->first);
	}
	FloatMap input = s->Receive(keys);
	for(FloatMap::iterator it = input.begin(); it != input.end(); ++it){
		*(critical_input[it->first]) = it->second;
	}
}

void ComThread::Critical_send(){
	s->Send(critical_output);
}
