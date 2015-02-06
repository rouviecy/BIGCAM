/*
 * @(#)		Share.h
 * @version	1.2
 * @autor	C. Rouvière
 */

/**
 * Shared data
 */

#ifndef SHARE
#define SHARE

#include <mutex>

class Share{

public:

	Share();
	void Lock();
	void Unlock();
	
	float	t;
	float	x,		y,		z;
	float	vx,		vy,		vz;
	float	thx,	thy,	thz;
	float	vthx,	vthy,	vthz;
	float	compas;
	float	gps_x,	gps_y;


private:

	std::mutex mu;

};

#endif
