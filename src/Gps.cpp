#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){
	#ifdef MODE_RASPI
		tty = serialOpen("/dev/ttyAMA0", 4800);
		if(tty < 0)					{cout << "Unable to open serial device" << endl;}
		if(wiringPiSetup () == -1)	{cout << "Unable to start wiringPi" << endl;}
		header[0] = '$';
		header[1] = 'G';
		header[2] = 'P';
		header[3] = 'G';
		header[4] = 'G';
		header[5] = 'A';
		is_header = false;
		valid_msg = false;
		index_header = 0;
		serialFlush(tty);
	#endif
}

void Gps::IO(){
	Link_output("gps_x", &gps_x);
	Link_output("gps_y", &gps_y);
	
	Link_input("simu_gps_x", &simu_gps_x);
	Link_input("simu_gps_y", &simu_gps_y);
}

void Gps::Job(){
	Critical_receive();
	#ifdef MODE_RASPI
		for(int i = 0; i < serialDataAvail(tty); i++){
			char nv = char(serialGetchar(tty));
			if(nv == '$'){
				is_header = true;
				valid_msg = true;
				index_header = 0;
				msg = "";
			}
			if(valid_msg && is_header){
				if(nv == header[index_header]){index_header++;}
				else{valid_msg = false;}
			}
			if(valid_msg && index_header == sizeof(header) / sizeof(char)){
				index_header = -1;
				is_header = false;
				continue;
			}
			if(valid_msg && !is_header){
				msg += nv;
			}
			if(valid_msg && nv == '*'){
				cout << msg << endl;
			}
		}
		gps_x = simu_gps_x;
		gps_y = simu_gps_y;
	#else
		gps_x = simu_gps_x;
		gps_y = simu_gps_y;
	#endif
	Critical_send();
}
