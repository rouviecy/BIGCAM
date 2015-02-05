#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){
	Topic topic_compas	("/from_compas");
	Topic topic_imu		("/from_imu");
	Topic topic_gps		("/from_gps");
	State state;
	Compas compas;

	usleep(5000000);

	state.Join();
	compas.Join();
	topic_compas.Close();
	topic_gps.Close();
	topic_imu.Close();
}
