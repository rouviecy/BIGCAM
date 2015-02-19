/*
 * @(#)		Mask.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Utilities to pull or push rotated rectangle images
 */

#ifndef MASK
#define MASK

#include <opencv2/opencv.hpp>
#include <vector>

class Mask{

public:

	static void Pick_and_place(			// Add an image to another one, at a position with an angle
		cv::Mat img_src,					// Little image to add
		cv::Mat img_dst,					// Big image which receives the little image
		cv::Point position,					// Position in the big image of the little image center
		float angle);						// Roation angle of the little image

private:

	static cv::Mat Mask_rotated_rect(	// Create a mask corresponding to a rotated rectangle
		cv::Size big_size,					// Size of the mask
		cv::Size little_size,				// Size of the rotated rectangle
		cv::Point position,					// Position of rotated rectangle center
		float angle);						// Rotation angle of rectangle

	static cv::Mat Rotation(			// Rotate an image around its center
		cv::Mat image,						// Input image
		float angle);						// Rotation angle

};

#endif
