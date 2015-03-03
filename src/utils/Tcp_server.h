#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

#ifndef TCP_SERVER
#define TCP_SERVER

class Tcp_server{

public:

	Tcp_server();
	char* Receive();
	void Close();

private:

	#define PORT		4242
	#define BUFF_LEN	1024

	int s;
	int cli;
	struct sockaddr_in self;
	char buffer[BUFF_LEN];

};

#endif
