#include "Motor.h"

using namespace std;

Motor::Motor() : Actuator(){
	#ifdef MODE_RASPI
		if(wiringPiSetup () == -1)						{cout << "Unable to start wiringPi" << endl;}
		if(softPwmCreate(GPIO_MOTOR, 0, 100) != 0)		{cout << "Unable to connect PWM motor" << endl;}
		if(softPwmCreate(GPIO_SERVO_L, 0, 100) != 0)	{cout << "Unable to connect PWM servo left" << endl;}
		if(softPwmCreate(GPIO_SERVO_R, 0, 100) != 0)	{cout << "Unable to connect PWM servo right" << endl;}
	#endif
}

void Motor::IO(){
	Link_input("v_motor", &v_motor);
	Link_input("wing_left", &wing_left);
	Link_input("wing_right", &wing_right);
}

void Motor::Job(){
	Critical_receive();
	int pwm_motor	= (int) (v_motor * 100.);
	int pwm_left	= (int) ((0.05 + wing_left) * 500.);
	int pwm_right	= (int) ((0.05 + wing_right) * 500.);
	#ifdef MODE_RASPI
		softPwmWrite(GPIO_MOTOR, pwm_motor);
		softPwmWrite(GPIO_SERVO_L, pwm_left);
		softPwmWrite(GPIO_SERVO_R, pwm_right);
	#else
		cout << "PWM : \t" << pwm_motor << "\t" << pwm_left << "\t" << pwm_right << endl;
	#endif
}
