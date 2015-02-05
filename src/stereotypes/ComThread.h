/*
 * @(#)		ComThread.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Thread with queue communication
 */

#ifndef COMTHREAD
#define COMTHREAD

#include <thread>

class ComThread{

public:

	ComThread();
	void Close();

private:

	char* name;
	std::thread thr;
	virtual void Job() = 0;

};

#endif
