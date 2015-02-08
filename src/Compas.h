/*
 * @(#)		Compas.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Information from compas
 */

#ifndef COMPAS
#define COMPAS

#include "stereotypes/Proprioceptive.h"

class Compas : public Proprioceptive {

public:

	Compas();

private:

	void Job();
	void IO();

	float compas;

};

#endif
