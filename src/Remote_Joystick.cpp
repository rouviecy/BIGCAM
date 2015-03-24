#include "Remote_Joystick.h"

using namespace std;

Remote_Joystick::Remote_Joystick() : ComThread(){
	last_motor = 0;
	last_turn = 5;
	last_balance = 5;
	last_head = 0;
}

void Remote_Joystick::IO(){

}

void Remote_Joystick::Wait_quit_from_user(){
	joystick.Connect_joystick(0);
	int* buttons = joystick.Get_buttons();
	int* axes = joystick.Get_axes();
	int* hats = joystick.Get_hats();
	bool continuer = true;
	axes[3] = +36000; // force motor stopped at the begining
	while(continuer){
		joystick.Update_event();
		if(buttons[0]){continuer = false; break;}
		Update_motor(Calib_power(-axes[3]));
		Update_turn(Calib_power(axes[0]));
		Update_balance(Calib_power(axes[1]));
		Update_head(hats[0]);
		usleep(20000);
	}
	joystick.Disconnect_joystick();
	cout << "Goodbye !" << endl;
	return;
}

int Remote_Joystick::Calib_power(int power_full_integer){
	if		(power_full_integer < -24000)	{return 0;}
	else if	(power_full_integer < -18000)	{return 1;}
	else if	(power_full_integer < -12000)	{return 2;}
	else if	(power_full_integer < -6000)	{return 3;}
	else if	(power_full_integer < 0)		{return 4;}
	else if	(power_full_integer < +6000)	{return 5;}
	else if	(power_full_integer < +12000)	{return 6;}
	else if	(power_full_integer < +18000)	{return 7;}
	else if	(power_full_integer < +24000)	{return 8;}
	else									{return 9;}
}

void Remote_Joystick::Update_motor(int power_0_10){
	if(last_motor != power_0_10){
		last_motor = power_0_10;
		Send_msg("M" + to_string(power_0_10));
	}
}

void Remote_Joystick::Update_turn(int power_0_10){
	if(last_turn != power_0_10){
		last_turn = power_0_10;
		Send_msg("T" + to_string(power_0_10));
	}
}

void Remote_Joystick::Update_balance(int power_0_10){
	if(last_balance != power_0_10){
		last_balance = power_0_10;
		Send_msg("B" + to_string(power_0_10));
	}
}

void Remote_Joystick::Update_head(int hat_status){
	if(last_head == 0 && (hat_status == SDL_HAT_LEFT || hat_status == SDL_HAT_LEFTUP || hat_status == SDL_HAT_LEFTDOWN)){
		last_head = -1;
		Send_msg("W1");
	}
	if(last_head == 0 && (hat_status == SDL_HAT_RIGHT || hat_status == SDL_HAT_RIGHTUP || hat_status == SDL_HAT_RIGHTDOWN)){
		last_head = +1;
		Send_msg("X1");
	}
	if(last_head == -1 && hat_status != SDL_HAT_LEFT && hat_status != SDL_HAT_LEFTUP && hat_status != SDL_HAT_LEFTDOWN
	|| last_head == +1 && hat_status != SDL_HAT_RIGHT && hat_status != SDL_HAT_RIGHTUP && hat_status != SDL_HAT_RIGHTDOWN){
		last_head = 0;
	}
}

void Remote_Joystick::Send_msg(string msg){
	cout << msg << endl;
//	char msg_serial[1024];
//	strncpy(msg, msg.c_str(), sizeof(msg_serial));
//	msg[sizeof(msg_serial) - 1] = '\0';
//	write(serial_port, msg_serial, 1024);
}

void Remote_Joystick::Job(){}

void Remote_Joystick::Set_serial_port(int serial_port){this->serial_port = serial_port;}
