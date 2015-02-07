#include "Remote.h"

using namespace std;

Remote::Remote() : ComThread(){
	is_remote = +1.;
	remote_power = 0.;
	remote_turn = 0.;
}

void Remote::IO(){
	Link_output("is_remote", &is_remote);
	Link_output("remote_power", &remote_power);
	Link_output("remote_turn", &remote_turn);
}

void Remote::Job(){
	cout << "test" << endl;
	Critical_send();
}
