/*
 * @(#)		ComThread.h
 * @version	1.1
 * @autor	C. Rouvière
 */

/**
 * Thread with message queue communication
 */

#ifndef COMTHREAD
#define COMTHREAD

#include <map>
#include <thread>
#include <mqueue.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

class ComThread{

public:

	ComThread();					// Create the thread
	void Join(						// Wait the end of the thread
		bool kill_topic = false);		// If topics must be killed

private:

	#define MAXMSG	10
	#define MSGLEN	1024
	std::thread thr;
	std::map<const char*, mqd_t> channels;

protected:

	virtual void Job() = 0;			// Overwrite : job for the thread
	void Subscribe(					// Listen a topic
		const char* topic_name,			// Name of the topic : "/XXX"
		bool create = false,			// If topic creation is allowed
		bool block = true);				// Blocking wait message
	void Send(						// Send a message
		const char* topic_name,			// Name of the topic : "/XXX"
		std::string message,			// Message to send
		int priority = 10);				// Priority (0 = very important)
	std::string Read(				// Receive a message from a topic
		const char* topic_name);		// Name of the topic : "/XXX"
	bool IsEmptyTopic(				// If there is any message in topic
		const char* topic_name);		// Name of the topic : "/XXX"

};

#endif
