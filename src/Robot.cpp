#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){
	vector <Topic> topics;
	Topic topic_compas	("/from_compas");
	Topic topic_imu		("/from_imu");
	Topic topic_gps		("/from_gps");
	Topic topic_motor	("/to_motor");
	Topic topic_servo	("/to_servo");
	Topic topic_odomcam	("/odom_to_cam");
	State state;
	Camera camera;
	Compas compas;
	Gps gps;
	Imu imu;
	Motor motor;
	Servo servo;

	usleep(50000000);

	state.Join();
	camera.Join();
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
	topic_odomcam.Close();
}
