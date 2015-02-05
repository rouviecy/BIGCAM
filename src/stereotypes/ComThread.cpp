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

void ComThread::Send(const char* topic_name, const char* message){
	mq_send(channels[topic_name], message, strlen(message), 10); // TODO 10
}

void ComThread::Subscribe(const char* topic_name, bool create){
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10; // never more than 10
	attr.mq_msgsize = 1024; // TODO
	attr.mq_curmsgs = 0;
	int flag = create ? O_RDWR | O_CREAT : O_RDWR;
	channels[topic_name] = mq_open(topic_name, flag, 0644, &attr);
}

string ComThread::Read(const char* topic_name){
	char msg_in[1024]; // TODO
	memset(msg_in, 0, 1024); // TODO
	mq_receive(channels[topic_name], msg_in, 1024, NULL);// TODO
	return string(msg_in);
}
