/*
 * @(#)		Motor.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Motor and servo-motors control by PWM over serial (connected to Pololu mini maestro 18)
 */

#ifndef MOTOR
#define MOTOR

#include "stereotypes/Actuator.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

class Motor : public Actuator{

public:

	Motor();
	~Motor();

private:

	#define PATH_DEV_MOTOR		"/dev/serial/by-id/usb-Pololu_Corporation_Pololu_Mini_Maestro_18-Channel_USB_Servo_Controller_00022159-if00"
	#define CHANNEL_MOTOR	0
	#define CHANNEL_LEFT	1
	#define CHANNEL_RIGHT	2
	#define CHANNEL_BACK	3

	void Job();
	void IO();

	float v_motor;
	float wing_left;
	float wing_right;
	float stab;

	int fd;

	void Generate_order(int pwm_0_to_100, int channel);
	void Generate_order2(int pwm_0_to_100, int channel);

};

#endif
