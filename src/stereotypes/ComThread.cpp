#include "ComThread.h"

using namespace std;

// Constructeur
ComThread::ComThread(){
	this->name = name;
	thr = thread(&ComThread::job, this);
}

void ComThread::Close(){thr.join();}
