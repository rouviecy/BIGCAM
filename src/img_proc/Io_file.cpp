#include "Io_file.h"

using namespace std;

Io_file::Io_file(){
	log_out.open(LOG_PATH, ios::app);
}

Io_file::~Io_file(){
	log_out.close();
}

void Io_file::Write(struct_img message){
	cv::imwrite(message.path + to_string(message.number) + ".png", message.img);
	log_out <<
		message.path << "\t" <<
		to_string(message.number) << "\t" <<
		message.x << "\t" <<
		message.y << "\t" <<
		message.z << endl;
}

vector <struct_img> Io_file::Read(){
	vector <struct_img> result;
	log_in.open(LOG_PATH);
	if(log_in.is_open()){
		string line;
		while(getline(log_in, line)){
			cout << line << endl;
		}
		log_in.close();
	}
	return result;
}

void Io_file::Clear_log(){
	log_out.close();
	remove(LOG_PATH);
	log_out.open(LOG_PATH, ios::app);
}
