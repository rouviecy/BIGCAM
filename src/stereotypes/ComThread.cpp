#include "ComThread.h"

using namespace std;

// Constructeur
ComThread::ComThread(){
	thr = thread(&ComThread::Job, this);
}

void ComThread::Close(){thr.join();}
