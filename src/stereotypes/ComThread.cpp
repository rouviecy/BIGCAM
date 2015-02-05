#include "ComThread.h"

using namespace std;

// Constructeur
ComThread::ComThread(){
	this->name = name;
	thr = thread(&ComThread::Job, this);
}

void ComThread::Close(){thr.join();}
