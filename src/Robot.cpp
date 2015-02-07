#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){

	// Warning : pass-by-reference to avoid slicing !
	threads.push_back(&state);
	threads.push_back(&camera);
	threads.push_back(&clock);
	threads.push_back(&compas);
	threads.push_back(&gps);
	threads.push_back(&imu);
	threads.push_back(&motor);
	threads.push_back(&servo);

	Link_all();
	Launch_all();

	usleep(50000000);

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
		threads[i]->Launch();
	}
}
