#include "Remote_rf.h"

using namespace std;

Remote_rf::Remote_rf() : ComThread(){
	is_remote = -1.;
	switch_alive = +1.;
	remote_power = 0.;
	remote_turn = 0.;
}

void Remote_rf::IO(){
	Link_output("is_remote", &is_remote);
	Link_output("switch_alive", &switch_alive);
	Link_output("remote_power", &remote_power);
	Link_output("remote_turn", &remote_turn);
	Link_output("remote_pitch", &remote_pitch);
	Link_output("remote_deriv", &remote_deriv);
}

void Remote_rf::Wait_quit_from_user(){
	char msg_in[255];
	int res;
	is_remote = +1.;
	for(;;){
		res = read(serial_port, msg_in, 255);
cout << "Received : " << msg_in[0] << msg_in[1] << endl;
		if		(msg_in[0] == 'A')	{is_remote = +1.;}
		else if (msg_in[0] == 'Z')	{is_remote = -1.;}
		else if (msg_in[0] == 'S')	{switch_alive = switch_alive < 0 ? +1. : -1.;}
		else if (msg_in[0] == '+')	{remote_power += 0.1;}
		else if (msg_in[0] == '-')	{remote_power -= 0.1;}
		else if (msg_in[0] == 'L')	{remote_turn = msg_in[1] == '1' ? -1.0 : 0.;}
		else if (msg_in[0] == 'R')	{remote_turn = msg_in[1] == '1' ? +1.0 : 0.;}
		else if (msg_in[0] == 'U')	{remote_pitch = msg_in[1] == '1' ? +1.0 : 0.;}
		else if (msg_in[0] == 'D')	{remote_pitch = msg_in[1] == '1' ? -1.0 : 0.;}
		else if (msg_in[0] == 'W')	{remote_deriv += msg_in[1] == '1' ? -0.2 : 0.;}
		else if (msg_in[0] == 'X')	{remote_deriv += msg_in[1] == '1' ? +0.2 : 0.;}
		else if (msg_in[0] == 'M')	{
			switch(msg_in[1]){
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
		else if (msg_in[0] == 'B')	{
			switch(msg_in[1]){
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
		else if (msg_in[0] == 'T')	{
			switch(msg_in[1]){
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
		else if (msg_in[0] == 'C')	{
			switch(msg_in[1]){
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
		else if (msg_in[0] == 'Q')	{usleep(2000000); break;}
		Smooth_order();
		Critical_send();
	}
	cout << "Goodbye !" << endl;
	return;
}

void Remote_rf::Job(){} // Do not use thread job (remember : Set_freq(-1))

void Remote_rf::Smooth_order(){
	if		(remote_power > +1.)	{remote_power = +1.;}
	else if (remote_power < +0.05)	{remote_power = +0.;}
	if		(remote_turn > +1.)		{remote_turn = +1.;}
	else if	(remote_turn < -1.)		{remote_turn = -1.;}
}

void Remote_rf::Set_serial_port(int serial_port){this->serial_port = serial_port;}
