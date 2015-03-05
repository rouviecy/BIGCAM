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
	if(listen(s, 1) != 0){
		perror(("Listen on port " + to_string(port)).c_str());
		exit(errno);
	}
	struct sockaddr_in client_addr;
	int addrlen = sizeof(client_addr);
	cli = accept(s, (struct sockaddr*) &client_addr, (socklen_t*) &addrlen);
	printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
}

char* Tcp_server::Receive(){
	recv(cli, buffer, TCP_BUFFER_LEN, 0);
	return buffer;
}

void Tcp_server::Send(string msg_out){
	char* msg = new char[TCP_BUFFER_LEN];
	copy(msg_out.begin(), msg_out.end(), msg);
	msg[msg_out.size()] = '\0';
	send(cli, msg, TCP_BUFFER_LEN, 0);
	delete[] msg;
}

void Tcp_server::Close(){
	close(cli);
	close(s);
}
