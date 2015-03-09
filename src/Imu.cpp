#include "Imu.h"

using namespace std;

Imu::Imu() : Proprioceptive(){
	imu_thx = 0.;	imu_thy = 0.;	imu_thz = 0.;
	#ifdef MODE_RASPI
		tty = serialOpen("/dev/ttyUSB0", 57600);
		if(tty < 0)					{cout << "Unable to open serial device" << endl;}
		if(wiringPiSetup () == -1)	{cout << "Unable to start wiringPi" << endl;}
		header[0] = '#';
		header[1] = 'Y';
		header[2] = 'P';
		header[3] = 'R';
		header[4] = '=';
		is_header = false;
		valid_msg = false;
		index_header = 0;
		serialFlush(tty);
	#endif
}

void Imu::IO(){
	Link_output("imu_thx", &imu_thx);
	Link_output("imu_thy", &imu_thy);
	Link_output("imu_thz", &imu_thz);
	Link_input("simu_compas", &simu_compas);
}

void Imu::Job(){
	Critical_receive();
	#ifdef MODE_RASPI
		for(int i = 0; i < serialDataAvail(tty); i++){
			char nv = char(serialGetchar(tty));
			if(nv == '#'){
				if(valid_msg){Decode_9DOF_RAZOR(msg);}
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
			if(valid_msg && !is_header){msg += nv;}
		}
	#else
		imu_thz = simu_compas;
	#endif
	Critical_send();
}

void Imu::Decode_9DOF_RAZOR(string msg_ypr){
	if(msg_ypr.size() < 19){return;}
	size_t next;
	vector <string> tokens;
	for(size_t current = 0; tokens.size() < 3; current = next + 1){
		next = msg_ypr.find_first_of(",", current);
		tokens.push_back(msg_ypr.substr(current, next - current));
	}
	float yaw			= stof(tokens[0]);
	float pitch			= stof(tokens[1]);
	float roll			= stof(tokens[2]);
	imu_thx = -pitch * DEG_TO_RAD;
	imu_thy = -roll * DEG_TO_RAD;
	imu_thz = -yaw * DEG_TO_RAD;
	cout << "thx, thy, thz = " << imu_thx << "\t" << imu_thy << "\t" << imu_thz << endl;
}
