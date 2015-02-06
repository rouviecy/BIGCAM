#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){
	state.Launch(&share);
	camera.Launch(&share);
	compas.Launch(&share);
	gps.Launch(&share);
	imu.Launch(&share);
	motor.Launch(&share);
	servo.Launch(&share);

	usleep(5000000);

	state.Join();
	camera.Join();
	compas.Join();
	gps.Join();
	imu.Join();
	motor.Join();
	servo.Join();
}
