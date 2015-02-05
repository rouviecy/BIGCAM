#include "Topic.h"

using namespace std;

Topic::Topic(const char* topic_name) : ComThread(){
	Subscribe(topic_name, true);
}

void Topic::Close(){Join(true);}

void Topic::Job(){}
