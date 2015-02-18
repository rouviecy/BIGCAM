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

	#define MARGIN_X 1000
	#define MARGIN_Y 1000

	Io_file io_file;
	std::vector <struct_img> list_img;

	void Pick_and_place(		// Add an image to another one, at a position with an angle
		cv::Mat img_src,			// Little image to add
		cv::Mat img_dst,			// Big image which receives the little image
		cv::Point position,			// Position in the big image of the little image center
		float angle);				// Roation angle of the little image

	cv::Mat Mask_rotated_rect(	// Create a mask corresponding to a rotated rectangle
		cv::Size big_size,			// Size of the mask
		cv::Size little_size,		// Size of the rotated rectangle
		cv::Point position,			// Position of rotated rectangle center
		float angle);				// Rotation angle of rectangle

	cv::Mat Rotation(			// Rotate an image around its center
		cv::Mat image,				// Input image
		float angle);				// Rotation angle

};

#endif
