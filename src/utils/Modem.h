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

typedef struct{float a; float b; float c;} struct_3f;

class Modem{

public:

	static std::string Enc_3f(float a, float b, float c);
	static struct_3f Dec_3f(std::string message);

};

#endif
