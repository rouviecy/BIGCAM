/*
 * @(#)		test.cpp
 * @version	1.0
 * @autor	C. Rouvière
 */

 /**
 *
 */

#include "../utils/Joystick.h"

using namespace std;

int main(){
	Joystick joystick;
	joystick.Connect_joystick(0);

	int* k = joystick.Get_buttons();

	while(true){
		joystick.Update_event();
		if(k[0]){break;}
	}
	
	joystick.Disconnect_joystick();
	return 0;
}
