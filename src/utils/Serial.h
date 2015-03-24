#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include <iostream>

#ifndef SERIAL
#define SERIAL

class Serial{

public:

	Serial();
	
	int Connect(const char* path_dev);
	void Disconnect();

private:

	int fd;
	struct termios tio_new, tio_old;

};

#endif
