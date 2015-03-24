#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){

	// Warning : pass-by-reference to avoid slicing !

	threads.push_back(&autonomy);
	threads.push_back(&camera);
	threads.push_back(&clock);
	threads.push_back(&gps);
	threads.push_back(&imu);
	threads.push_back(&motor);
	threads.push_back(&pressure);
	threads.push_back(&remote_rf);
	threads.push_back(&state_rf);
	#ifndef MODE_RASPI
		threads.push_back(&simulator);
	#endif

	int serial_port = serial.Connect("/dev/serial/by-id/usb-Arduino__www.arduino.cc__Arduino_USB-Serial_A4131363239351D070E0-if00");
	remote_rf.Set_serial_port(serial_port);
	state_rf.Set_serial_port(serial_port);

	clock.Set_name("Internal clock");			clock.Set_freq(1000);		// 1 ms
	imu.Set_name("Inertial Measurement Unit");	imu.Set_freq(50000);		// 50 ms
	gps.Set_name("Global Positioning System");	gps.Set_freq(100000);		// 100 ms
	pressure.Set_name("Pressure");				pressure.Set_freq(100000);	// 100 ms
	autonomy.Set_name("Autonomy");				autonomy.Set_freq(10000);	// 10 ms
	state_rf.Set_name("State RF");				state_rf.Set_freq(50000);	// 50 ms
	simulator.Set_name("Simulator");			simulator.Set_freq(10000);	// 10 ms
	remote_rf.Set_name("Remote RF");			remote_rf.Set_freq(-1);		// manual loop
	motor.Set_name("Motor");					motor.Set_freq(20000);		// 20 ms
	camera.Set_name("Camera");					camera.Set_freq(100000);	// 100 ms

	Link_all();
	Launch_all();

	remote_rf.Wait_quit_from_user();

	Join_all();
	serial.Disconnect();
}

void Robot::Link_all(){
	for(size_t i = 0; i < threads.size(); i++){
		threads[i]->Link(&share);
	}
	drawer.Draw_threads(threads);
}

void Robot::Launch_all(){
	for(size_t i = 0; i < threads.size(); i++){
		threads[i]->Launch();
	}
}

void Robot::Join_all(){
	for(size_t i = 0; i < threads.size(); i++){
		threads[i]->Join();
	}
}
