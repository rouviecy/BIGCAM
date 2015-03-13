#include "Motor.h"

using namespace std;

Motor::Motor() : Actuator(){
	fd = open(PATH_DEV_MOTOR, O_RDWR | O_NOCTTY);
}

Motor::~Motor(){
	Generate_order(0,	CHANNEL_MOTOR);
	Generate_order(50,	CHANNEL_LEFT);
	Generate_order(50,	CHANNEL_RIGHT);
	Generate_order(50,	CHANNEL_BACK);
}

void Motor::IO(){
	Link_input("v_motor", &v_motor);
	Link_input("wing_left", &wing_left);
	Link_input("wing_right", &wing_right);
	Link_input("stab", &stab);
}

void Motor::Job(){
	Critical_receive();
	int pwm_motor	= (int) (v_motor * 100.);
	int pwm_left	= (int) ((1. + wing_left) * 50.);
	int pwm_right	= (int) ((1. + wing_right) * 50.);
	int pwm_back	= (int) ((1. + stab) * 50.);
	Generate_order(pwm_motor,	CHANNEL_MOTOR);
	Generate_order(pwm_left,	CHANNEL_LEFT);
	Generate_order(pwm_right,	CHANNEL_RIGHT);
	Generate_order(pwm_back,	CHANNEL_BACK);
}

void Motor::Generate_order(int pwm_0_to_100, int channel){
	unsigned short target = 4000 + ((unsigned short) pwm_0_to_100) * 40;
	unsigned char cmd[] = {0x84, (unsigned char) channel, (unsigned char) (target & 0x7F), (unsigned char) (target >> 7 & 0x7F)};
	write(fd, cmd, sizeof(cmd));
}
