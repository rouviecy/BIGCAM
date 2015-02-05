#include "Io_file.h"

using namespace std;

Io_file::Io_file(){
	log_out.open(LOG_PATH);
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

void Io_file::Clear_log(){remove(LOG_PATH);}
