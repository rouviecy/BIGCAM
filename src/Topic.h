/*
 * @(#)		Topic.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Class
 */

#ifndef TOPIC
#define TOPIC

#include "stereotypes/ComThread.h"

class Topic : public ComThread{

public:

	Topic(const char* topic_name, bool block = true);
	void Close();

private:

	void Job();

};

#endif
