#include "CPP_Remote.h"

using namespace std;

CPP_Remote::CPP_Remote(){

	// Warning : pass-by-reference to avoid slicing !

	threads.push_back(&joystick);
	threads.push_back(&monitor);

//	int serial_port = serial.Connect("/dev/serial/by-id/usb-FTDI_TTL232R-3V3_FTH0D7TW-if00-port0");
//	joystick.Set_serial_port(serial_port);
//	monitor.Set_serial_port(serial_port);

	joystick.Set_name("Joystick");	joystick.Set_freq(-1);
	monitor.Set_name("Monitor");	monitor.Set_freq(50000);

	Link_all();
	Launch_all();

	joystick.Wait_quit_from_user();

	Join_all();
//	serial.Disconnect();

}

void CPP_Remote::Link_all(){
	for(size_t i = 0; i < threads.size(); i++){
		threads[i]->Link(&share);
	}
	drawer.Draw_threads(threads);
}

void CPP_Remote::Launch_all(){
	for(size_t i = 0; i < threads.size(); i++){
		threads[i]->Launch();
	}
}

void CPP_Remote::Join_all(){
	for(size_t i = 0; i < threads.size(); i++){
		threads[i]->Join();
	}
}
