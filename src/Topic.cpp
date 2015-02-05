#include "Topic.h"

using namespace std;

Topic::Topic(const char* topic_name, bool block) : ComThread(){
	Subscribe(topic_name, true, block);
}

void Topic::Close(){Join(true);}

void Topic::Job(){}
