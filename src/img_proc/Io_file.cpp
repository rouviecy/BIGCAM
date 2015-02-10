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
			size_t next;
			vector <string> tokens;
			for(size_t current = 0; tokens.size() < 5; current = next + 1){
				next = line.find_first_of("\t", current);
				tokens.push_back(line.substr(current, next - current));
			}
			struct_img nv_img;
			nv_img.path = tokens[0] + tokens[1] + ".png";
			nv_img.img = cv::imread(nv_img.path);
			nv_img.x = stof(tokens[2]);
			nv_img.y = stof(tokens[3]);
			nv_img.z = stof(tokens[4]);
			result.push_back(nv_img);
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
