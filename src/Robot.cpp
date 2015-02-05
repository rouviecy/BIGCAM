#include "Robot.h"

using namespace std;

// Constructeur
Robot::Robot(){
	Topic topic_compas("/from_compas");
	State state;
	Compas compas;

	usleep(5000000);

	state.Join();
	compas.Join();
	topic_compas.Close();
}
