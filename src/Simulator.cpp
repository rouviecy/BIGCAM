#include "Simulator.h"

using namespace std;

Simulator::Simulator() : ComThread(){
	simu_gps_x = 0.;
	simu_gps_y = 0.;
	simu_compas = 0.;
}

void Simulator::IO(){
	Link_input("x", &x);
	Link_input("y", &y);
	Link_input("thz", &thz);

	Link_output("simu_gps_x", &simu_gps_x);
	Link_output("simu_gps_y", &simu_gps_y);
	Link_output("simu_compas", &simu_compas);

	Link_input("v_motor", &v_motor);
	Link_input("steer", &steer);
	Link_input("wing_left", &wing_left);
	Link_input("wing_right", &wing_right);
}

void Simulator::Job(){
	Critical_receive();
	simu_compas = thz + v_motor * (-wing_left + wing_right + steer);
	simu_gps_x = x + cos((float) thz) * v_motor;
	simu_gps_y = y + sin((float) thz) * v_motor;
	Critical_send();
}
