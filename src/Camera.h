/*
 * @(#)		Camera.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Data from camera
 */

#ifndef CAMERA
#define CAMERA

#include "stereotypes/Exteroceptive.h"

class Camera : public Exteroceptive{

public:

	Camera();

private:

	void Job();

};

#endif
