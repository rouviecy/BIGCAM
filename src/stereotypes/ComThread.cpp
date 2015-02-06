#include "ComThread.h"

using namespace std;

ComThread::ComThread(){
	
}

void ComThread::Launch(Share *s){
	this->s = s;
	thr = thread(&ComThread::Job, this);
}

void ComThread::Join(){
	thr.join();
}
