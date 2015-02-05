#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){
	Topic topic_compas	("/from_compas");
	Topic topic_imu		("/from_imu");
	Topic topic_gps		("/from_gps");
	Topic topic_motor	("/to_motor");
	Topic topic_servo	("/to_servo");
	State state;
	Compas compas;
	Gps gps;
	Imu imu;
	Motor motor;
	Servo servo;

	usleep(5000000);

	state.Join();
	compas.Join();
	gps.Join();
	imu.Join();
	motor.Join();
	servo.Join();
	topic_compas.Close();
	topic_gps.Close();
	topic_imu.Close();
	topic_motor.Close();
	topic_servo.Close();
}
