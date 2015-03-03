#include "Tcp_server.h"

Tcp_server::Tcp_server(){
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Socket");
		exit(errno);
	}
	bzero(&self, sizeof(self));
	self.sin_family			= AF_INET;
	self.sin_port			= htons(PORT);
	self.sin_addr.s_addr	= INADDR_ANY;
    if(bind(s, (struct sockaddr*) &self, sizeof(self)) != 0){
		perror("Bind");
		exit(errno);
	}
	if(listen(s, 20) != 0){
		perror("Listen");
		exit(errno);
	}
	struct sockaddr_in client_addr;
	int addrlen = sizeof(client_addr);
	cli = accept(s, (struct sockaddr*) &client_addr, (socklen_t*) &addrlen);
	printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
}

char* Tcp_server::Receive(){
	send(cli, buffer, recv(cli, buffer, BUFF_LEN, 0), 0);
	return buffer;
}

void Tcp_server::Close(){
	close(cli);
	close(s);
}

