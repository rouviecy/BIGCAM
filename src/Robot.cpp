#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){

	// Warning : pass-by-reference to avoid slicing !
	threads.push_back(&state);
	threads.push_back(&autonomy);
	threads.push_back(&camera);
	threads.push_back(&clock);
	threads.push_back(&compas);
	threads.push_back(&gps);
	threads.push_back(&imu);
	threads.push_back(&motor);
	threads.push_back(&remote);
	threads.push_back(&servo);

	clock.Set_freq(1000);		// 1 ms
	imu.Set_freq(10000);		// 10 ms
	compas.Set_freq(100000);	// 100 ms
	gps.Set_freq(10000000);		// 10 s
	autonomy.Set_freq(50000);	// 50 ms
	state.Set_freq(50000);		// 50 ms
	remote.Set_freq(-1);		// manual loop
	motor.Set_freq(100000);		// 100 ms
	servo.Set_freq(100000);		// 100 ms
	camera.Set_freq(1000000);	// 1 s

	Link_all();
	Launch_all();

	usleep(5000000);

	Join_all();
}

void Robot::Link_all(){
	for(size_t i = 0; i < threads.size(); i++){
		threads[i]->Link(&share);
	}
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
