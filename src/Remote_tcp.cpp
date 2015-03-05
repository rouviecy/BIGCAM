#include "Remote_tcp.h"

using namespace std;

Remote_tcp::Remote_tcp() : ComThread(){
	is_remote = +1.;
	remote_power = 0.;
	remote_turn = 0.;
	tcp_server_in.Configure(TCP_PORT_IN);
}

void Remote_tcp::IO(){
	Link_output("is_remote", &is_remote);
	Link_output("remote_power", &remote_power);
	Link_output("remote_turn", &remote_turn);
}

void Remote_tcp::Wait_quit_from_user(){
	for(;;){
		char* msg_in = tcp_server_in.Receive();
		char key = (char) *msg_in;
		if		(key == 'A')	{is_remote = +1.;}
		else if (key == 'Z')	{is_remote = -1.;}
		else if (key == '+')	{remote_power += 0.1;}
		else if (key == '-')	{remote_power -= 0.1;}
		else if (key == 'L')	{remote_turn = -0.5;}
		else if (key == 'R')	{remote_turn = +0.5;}
		else if (key == 'Q')	{usleep(2000000); tcp_server_in.Close(); break;}
		Smooth_order();
		Critical_send();
	}
	cout << "Goodbye !" << endl;
	return;
}

void Remote_tcp::Job(){} // Do not use thread job (remember : Set_freq(-1))

void Remote_tcp::Smooth_order(){
	if		(remote_power > +1.)	{remote_power = +1.;}
	else if (remote_power < +0.05)	{remote_power = +0.;}
	if		(remote_turn > +1.)		{remote_turn = +1.;}
	else if	(remote_turn < -1.)		{remote_turn = -1.;}
}
