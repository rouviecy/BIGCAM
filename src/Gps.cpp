#include "Gps.h"

using namespace std;

Gps::Gps() : Proprioceptive(){
	gps_x = 0.;
	gps_y = 0.;
	#ifdef MODE_RASPI
		tty = serialOpen(PATH_DEV_GPS, 4800);
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
	first = true;
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
			if(valid_msg && !is_header){msg += nv;}
			if(valid_msg && nv == '*'){Decode_NMEA(msg);}
		}
	#else
		gps_x = simu_gps_x;
		gps_y = simu_gps_y;
	#endif
	Critical_send();
}

void Gps::Decode_NMEA(string msg_nmea){
	if(msg_nmea.size() < 37){return;}
	size_t next;
	vector <string> tokens;
	for(size_t current = 0; tokens.size() < 6; current = next + 1){
		next = msg_nmea.find_first_of(",", current);
		tokens.push_back(msg_nmea.substr(current, next - current));
	}
	if(	tokens[1].size() < 6 or
		tokens[2].size() < 7 or
		tokens[3].size() < 1 or
		tokens[4].size() < 7 or
		tokens[5].size() < 1){
			cout << "GPS ERROR" << endl;
			return;
	}
	int hh			= stoi(tokens[1].substr(0, 2));
	int mm			= stoi(tokens[1].substr(2, 2));
	int ss			= stoi(tokens[1].substr(4, 2));
	int lat_dd		= stoi(tokens[2].substr(0, 2));
	float lat_mm	= stof(tokens[2].substr(2, 7));
	int lon_dd		= stoi(tokens[4].substr(0, 3));
	float lon_mm	= stof(tokens[4].substr(3, 7));
	bool is_N		= (tokens[3].compare("N") == 0);
	bool is_W		= (tokens[5].compare("W") == 0);
	float lat_float = ((float) lat_dd) * M_PI / 180. + lat_mm * M_PI / 10800.;
	float lon_float = ((float) lon_dd) * M_PI / 180. + lon_mm * M_PI / 10800.;
	float x = (is_N ? +1. : -1.) * R_EARTH * cos(lat_float) * cos(lon_float);
	float y = (is_W ? -1. : +1.) * R_EARTH * cos(lat_float) * sin(lon_float);
	if(first){
		offset_x = x;
		offset_y = y;
		first = false;
	}
	gps_x = x - offset_x;
	gps_y = y - offset_y;
	cout << gps_x << "\t" << gps_y << endl;
}
