#include "ComThread.h"

using namespace std;

ComThread::ComThread(){
	dt_microseconds = 1000000;
}

void ComThread::Link(Share *s){
	this->s = s;
	IO();
}

void ComThread::Launch(){
	job_go_on = true;
	thr = thread(&ComThread::Loop_job, this);

}

void ComThread::Join(){
	job_go_on = false;
	thr.join();
}

void ComThread::Loop_job(){
	if(dt_microseconds > 0){
		while(job_go_on){
			Job();
			usleep(dt_microseconds);
		}
	}
	else{
		Job();
	}
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

void ComThread::Critical_send(){s->Send(critical_output);}

void ComThread::Set_freq(int dt_microseconds){this->dt_microseconds = dt_microseconds;}
