/*
 * @(#)		ComThread.h
 * @version	1.3
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
	void Link(						// Link to shared memory
		Share *s);						// Pointer to share object
	void Launch();					// Begin the job
	void Join();					// Wait the end of the thread

private:

	std::thread thr;
	Share *s;
	PFloatMap critical_input, critical_output;

protected:

	virtual void Job() = 0;			// Overwrite : job for the thread
	virtual void IO() = 0;			// Overwrite : input and output links

	void Link_input(std::string key, float *p_float);
	void Link_output(std::string key, float *p_float);
	void Critical_receive();
	void Critical_send();

};

#endif
