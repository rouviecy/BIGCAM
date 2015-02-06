#include "Modem.h"

using namespace std;

std::string Modem::Enc_3f(float a, float b, float c){
	return to_string(a) + " " + to_string(b) + " " + to_string(c);
}

struct_3f Modem::Dec_3f(std::string message){
	struct_3f result;
	size_t current = 0;
	size_t next = message.find_first_of(" ", current);
	result.a = stof(message.substr(current, next - current));
	current = next + 1;
	next = message.find_first_of(" ", current);
	result.b = stof(message.substr(current, next - current));
	current = next + 1;
	next = message.find_first_of(" ", current);
	result.c = stof(message.substr(current, next - current));
	return result;
}
