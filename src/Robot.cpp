#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){

	// Warning : pass-by-reference to avoid slicing !

	threads.push_back(&autonomy);
	threads.push_back(&camera);
	threads.push_back(&clock);
	threads.push_back(&compas);
	threads.push_back(&gps);
	threads.push_back(&imu);
	threads.push_back(&monitor);
	threads.push_back(&motor);
	threads.push_back(&remote);
	threads.push_back(&servo);
	threads.push_back(&simulator);
	threads.push_back(&state);

	remote.Link_images(monitor.Get_img_monitor());

	clock.Set_name("Internal clock");			clock.Set_freq(1000);		// 1 ms
	imu.Set_name("Inertial Measurement Unit");	imu.Set_freq(10000);		// 10 ms
	compas.Set_name("Compass");					compas.Set_freq(100000);	// 100 ms
	gps.Set_name("Global Positioning System");	gps.Set_freq(10000);		// 10 ms
	autonomy.Set_name("Autonomy");				autonomy.Set_freq(50000);	// 50 ms
	state.Set_name("State");					state.Set_freq(50000);		// 50 ms
	simulator.Set_name("Simulator");			simulator.Set_freq(10000);	// 10 ms
	remote.Set_name("Remote Controller");		remote.Set_freq(-1);		// manual loop
	monitor.Set_name("Monitor");				monitor.Set_freq(50000);	// 50 ms
	motor.Set_name("Motor");					motor.Set_freq(100000);		// 100 ms
	servo.Set_name("Servo");					servo.Set_freq(100000);		// 100 ms
	camera.Set_name("Camera");					camera.Set_freq(1000000);	// 1 s

	Link_all();
	Launch_all();

	remote.Wait_quit_from_user();

	Join_all();
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
