/*
 * @(#)		Remote_Joystick.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * 
 */

#ifndef REMOTE_JOYSTICK
#define REMOTE_JOYSTICK

#include "stereotypes/ComThread.h"
#include "utils/Joystick.h"
#include "utils/Serial.h"

class Remote_Joystick : public ComThread{

public:

	Remote_Joystick();
	void Wait_quit_from_user();
	void Set_serial_port(int serial_port);

private:

	Joystick joystick;
	int serial_port;

	int last_motor, last_turn, last_balance, last_head;

	void Job();
	void IO();

	int Calib_power(int power_full_integer);
	void Update_motor(int power_0_10);
	void Update_turn(int power_0_10);
	void Update_balance(int power_0_10);
	void Update_head(int hat_status);
	void Send_msg(std::string msg);

};

#endif
