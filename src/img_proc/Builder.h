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
#include <opencv2/opencv.hpp>
#include <vector>

class Builder{

public:

	Builder();
	void Retrieve_pictures();
	void Build();


private:

	Io_file io_file;
	std::vector <struct_img> list_img;

};

#endif
