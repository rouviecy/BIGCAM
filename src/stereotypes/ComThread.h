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
#include <queue>
#include <map>

class ComThread{

public:

	ComThread();
	void Close();

private:

	std::thread thr;
	std::map<std::string, std::queue <std::string> > channels;

	virtual void Job() = 0;

};

#endif
