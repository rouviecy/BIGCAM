#include "Serial.h"

using namespace std;

Serial::Serial(){}

int Serial::Connect(const char* path_dev){
	fd = open(path_dev, O_RDWR | O_NOCTTY); //  | O_NDELAY | O_NONBLOCK
	memset(&tio_new, 0, sizeof(tio_new));
	tcgetattr(fd, &tio_old);
	cfsetispeed(&tio_new, B4800); // TODO : baud rate argument
	cfsetospeed(&tio_new, B4800);
	tio_new.c_cflag		&= ~PARENB;
	tio_new.c_cflag		&= ~CSTOPB;
	tio_new.c_cflag		&= ~CSIZE;
	tio_new.c_cflag		|= CS8;
	tio_new.c_cflag		&= ~CRTSCTS;
	tio_new.c_cflag		|= CREAD | CLOCAL;
	tio_new.c_iflag		&= ~(IXON | IXOFF | IXANY);
	tio_new.c_iflag		&= ~(ICANON | ECHO | ECHOE | ISIG);
	tio_new.c_oflag		&= ~OPOST;
	tio_new.c_cc[VMIN]	= 1;
	tcsetattr(fd, TCSANOW, &tio_new);
	tcflush(fd, TCIFLUSH);
	return fd;
}

void Serial::Disconnect(){
	tcsetattr(fd, TCSANOW, &tio_old);
}
