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
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <unistd.h>
#include <iostream>

class ComThread{

public:

	ComThread();
	void Join(bool kill_topic = false);

	void Send(const char* topic_name, const char* message);

private:

	std::thread thr;
	std::map<const char*, mqd_t> channels;

protected:

	virtual void Job() = 0;
	void Subscribe(const char* topic_name, bool create = false);
	std::string Read(const char* topic_name);

};

#endif
