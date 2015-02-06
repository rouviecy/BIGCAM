#include "ComThread.h"

using namespace std;

ComThread::ComThread(){
	thr = thread(&ComThread::Job, this);
}

void ComThread::Join(bool kill_topic){
	for(map<const char*,  mqd_t>::iterator it = channels.begin(); it != channels.end(); it++){
		mq_close(it->second);
		if(kill_topic){mq_unlink(it->first);}
	}
	thr.join();
}

void ComThread::Subscribe(const char* topic_name, bool create, bool block){
	struct mq_attr attr;
	attr.mq_flags = block ? 0 : O_NONBLOCK;
	attr.mq_maxmsg = MAXMSG;
	attr.mq_msgsize = MSGLEN;
	attr.mq_curmsgs = 0;
	int flag = create ? O_RDWR | O_CREAT : O_RDWR;
	channels[topic_name] = mq_open(topic_name, flag, 0644, &attr);
}

void ComThread::Send(const char* topic_name, string message, int priority){
	mq_send(channels[topic_name], message.c_str(), strlen(message.c_str()), priority);
}

string ComThread::Read(const char* topic_name){
	char message[MSGLEN];
	memset(message, 0, MSGLEN);
	mq_receive(channels[topic_name], message, MSGLEN, NULL);
	return string(message);
}

bool ComThread::Is_empty_topic(const char* topic_name){
	struct mq_attr attr;
	mq_getattr(channels[topic_name], &attr);
	int nb_messages = attr.mq_curmsgs;
	return nb_messages == 0;
}

void ComThread::Clear_topic(const char* topic_name){
	while(!Is_empty_topic(topic_name)){
		Read(topic_name);
	}
}
