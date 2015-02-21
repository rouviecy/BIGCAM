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
#include <cmath>

typedef struct{
	int index;
	int x_origin_prev;
	int y_origin_prev;
	float thz_origin_prev;
	int x_origin_next;
	int y_origin_next;
	float thz_origin_next;
	std::vector <cv::Point2i> amers_prev;
	std::vector <cv::Point2i> amers_next;
} struct_link_amers;

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
	
	std::vector <struct_link_amers> amers;

};

#endif
