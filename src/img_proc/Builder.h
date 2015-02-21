/*
 * @(#)		Builder.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Build a map
 */

#ifndef BUILDER
#define BUILDER

#include "Io_file.h"
#include "Mask.h"
#include "Tracking.h"
#include <opencv2/opencv.hpp>
#include <vector>

class Builder{

public:

	Builder();
	void Retrieve_pictures();
	void Build();

private:

	#define MARGIN_X 1000
	#define MARGIN_Y 1000

	Io_file io_file;
	Tracking tracking;
	std::vector <struct_img> list_img;

};

#endif
