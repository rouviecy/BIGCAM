#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){
	state.Link(&share);
	camera.Link(&share);
	clock.Link(&share);
	compas.Link(&share);
	gps.Link(&share);
//	imu.Link(&share);
//	motor.Link(&share);
//	servo.Link(&share);

	state.Launch();
	camera.Launch();
	clock.Launch();
	compas.Launch();
	gps.Launch();
//	imu.Launch();
//	motor.Launch();
//	servo.Launch();

	usleep(5000000);

	state.Join();
	camera.Join();
	clock.Join();
	compas.Join();
	gps.Join();
//	imu.Join();
//	motor.Join();
//	servo.Join();
}
