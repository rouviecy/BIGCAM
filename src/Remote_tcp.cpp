#include "Remote_tcp.h"

using namespace std;

Remote_tcp::Remote_tcp() : ComThread(){
	is_remote = +1.;
	is_tcp_remote = +1.;
	remote_power = 0.;
	remote_turn = 0.;
}

void Remote_tcp::IO(){
	Link_output("is_remote", &is_remote);
	Link_output("is_tcp_remote", &is_tcp_remote);
	Link_output("remote_power", &remote_power);
	Link_output("remote_turn", &remote_turn);
}

void Remote_tcp::Job(){
	char* msg_in = tcp_server.Receive();
	char key = (char) *msg_in;
	if		(key == 'A')	{is_remote = +1.;}
	else if (key == 'Z')	{is_remote = -1.;}
	else if (key == '+')	{remote_power += 0.1;}
	else if (key == '-')	{remote_power -= 0.1;}
	else if (key == 'L')	{remote_turn = -0.5;}
	else if (key == 'R')	{remote_turn = +0.5;}
	else if (key == 'Q')	{is_tcp_remote = -1.; Critical_send(); tcp_server.Close();}
	Smooth_order();
	Critical_send();
}

void Remote_tcp::Smooth_order(){
	if		(remote_power > +1.)	{remote_power = +1.;}
	else if (remote_power < +0.05)	{remote_power = +0.;}
	if		(remote_turn > +1.)		{remote_turn = +1.;}
	else if	(remote_turn < -1.)		{remote_turn = -1.;}
}
