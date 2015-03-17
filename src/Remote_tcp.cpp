#include "Remote_tcp.h"

using namespace std;

Remote_tcp::Remote_tcp() : ComThread(){
	is_remote = -1.;
	switch_alive = +1.;
	remote_power = 0.;
	remote_turn = 0.;
	tcp_server_in.Configure(TCP_PORT_IN);
}

void Remote_tcp::IO(){
	Link_output("is_remote", &is_remote);
	Link_output("switch_alive", &switch_alive);
	Link_output("remote_power", &remote_power);
	Link_output("remote_turn", &remote_turn);
	Link_output("remote_pitch", &remote_pitch);
	Link_output("remote_deriv", &remote_deriv);
}

void Remote_tcp::Wait_quit_from_user(){
	is_remote = +1.;
	for(;;){
		char* msg_in = tcp_server_in.Receive();
		char key = (char) *msg_in;
		if		(key == 'A')	{is_remote = +1.;}
		else if (key == 'Z')	{is_remote = -1.;}
		else if (key == 'S')	{switch_alive = switch_alive < 0 ? +1. : -1.;}
		else if (key == '+')	{remote_power += 0.1;}
		else if (key == '-')	{remote_power -= 0.1;}
		else if (key == 'L')	{remote_turn = (char) *(msg_in + sizeof(char)) == '1' ? -1.0 : 0.;}
		else if (key == 'R')	{remote_turn = (char) *(msg_in + sizeof(char)) == '1' ? +1.0 : 0.;}
		else if (key == 'U')	{remote_pitch = (char) *(msg_in + sizeof(char)) == '1' ? +1.0 : 0.;}
		else if (key == 'D')	{remote_pitch = (char) *(msg_in + sizeof(char)) == '1' ? -1.0 : 0.;}
		else if (key == 'W')	{remote_deriv += (char) *(msg_in + sizeof(char)) == '1' ? -0.2 : 0.;}
		else if (key == 'X')	{remote_deriv += (char) *(msg_in + sizeof(char)) == '1' ? +0.2 : 0.;}
		else if (key == 'M')	{
			switch((char) *(msg_in + sizeof(char))){
				case '0':	remote_power = 0.0; break;
				case '1':	remote_power = 0.1; break;
				case '2':	remote_power = 0.2; break;
				case '3':	remote_power = 0.3; break;
				case '4':	remote_power = 0.4; break;
				case '5':	remote_power = 0.5; break;
				case '6':	remote_power = 0.6; break;
				case '7':	remote_power = 0.7; break;
				case '8':	remote_power = 0.8; break;
				case '9':	remote_power = 1.0; break;
			}
		}
		else if (key == 'B')	{
			switch((char) *(msg_in + sizeof(char))){
				case '0':	remote_pitch = -1.0; break;
				case '1':	remote_pitch = -0.8; break;
				case '2':	remote_pitch = -0.6; break;
				case '3':	remote_pitch = -0.4; break;
				case '4':	remote_pitch = +0.0; break;
				case '5':	remote_pitch = +0.0; break;
				case '6':	remote_pitch = +0.4; break;
				case '7':	remote_pitch = +0.6; break;
				case '8':	remote_pitch = +0.8; break;
				case '9':	remote_pitch = +1.0; break;
			}
		}
		else if (key == 'T')	{
			switch((char) *(msg_in + sizeof(char))){
				case '0':	remote_turn = -1.0; break;
				case '1':	remote_turn = -0.8; break;
				case '2':	remote_turn = -0.6; break;
				case '3':	remote_turn = -0.4; break;
				case '4':	remote_turn = +0.0; break;
				case '5':	remote_turn = +0.0; break;
				case '6':	remote_turn = +0.4; break;
				case '7':	remote_turn = +0.6; break;
				case '8':	remote_turn = +0.8; break;
				case '9':	remote_turn = +1.0; break;
			}
		}
		else if (key == 'C')	{
			switch((char) *(msg_in + sizeof(char))){
				case '0':	remote_deriv = -1.0; break;
				case '1':	remote_deriv = -0.8; break;
				case '2':	remote_deriv = -0.6; break;
				case '3':	remote_deriv = -0.4; break;
				case '4':	remote_deriv = +0.0; break;
				case '5':	remote_deriv = +0.0; break;
				case '6':	remote_deriv = +0.4; break;
				case '7':	remote_deriv = +0.6; break;
				case '8':	remote_deriv = +0.8; break;
				case '9':	remote_deriv = +1.0; break;
			}
		}
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
