/*
 * @(#)		ComThread.h
 * @version	1.2
 * @autor	C. Rouvière
 */

/**
 * Thread with message queue communication
 */

#ifndef COMTHREAD
#define COMTHREAD

#include <thread>
#include <unistd.h>
#include <iostream>
#include "../Share.h"

class ComThread{

public:

	ComThread();					// Create the thread
	void Launch(					// Begin the job
		Share *s);						// Link to shared data
	void Join();					// Wait the end of the thread

private:

	std::thread thr;

protected:

	Share *s;
	virtual void Job() = 0;			// Overwrite : job for the thread

};

#endif
