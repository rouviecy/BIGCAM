/*
 * @(#)		Modem.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Encode and decode string messages
 */

#ifndef MODEM
#define MODEM

#include <string>

typedef struct{float a; float b;} struct_2f;
typedef struct{float a; float b; float c;} struct_3f;

class Modem{

public:

	static std::string Enc_1f(float a);
	static std::string Enc_2f(float a, float b);
	static std::string Enc_3f(float a, float b, float c);
	static float Dec_1f(std::string message);
	static struct_2f Dec_2f(std::string message);
	static struct_3f Dec_3f(std::string message);

};

#endif
