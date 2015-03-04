#include "Tcp_server.h"

using namespace std;

Tcp_server::Tcp_server(){}

void Tcp_server::Configure(int port){
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror(("Socket on port " + to_string(port)).c_str());
		exit(errno);
	}
	bzero(&self, sizeof(self));
	self.sin_family			= AF_INET;
	self.sin_port			= htons(port);
	self.sin_addr.s_addr	= INADDR_ANY;
    if(bind(s, (struct sockaddr*) &self, sizeof(self)) != 0){
		perror(("Bind on port " + to_string(port)).c_str());
		exit(errno);
	}
	if(listen(s, 20) != 0){
		perror(("Listen on port " + to_string(port)).c_str());
		exit(errno);
	}
	struct sockaddr_in client_addr;
	int addrlen = sizeof(client_addr);
	cli = accept(s, (struct sockaddr*) &client_addr, (socklen_t*) &addrlen);
	printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
}

char* Tcp_server::Receive(){
	recv(cli, buffer, BUFF_LEN, 0);
	return buffer;
}

void Tcp_server::Send(char* msg_out){
	send(cli, msg_out, BUFF_LEN, 0);
}

void Tcp_server::Close(){
	close(cli);
	close(s);
}
