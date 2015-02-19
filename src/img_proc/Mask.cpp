#include "Mask.h"

using namespace std;

void Mask::Pick_and_place(cv::Mat img_src, cv::Mat img_dst, cv::Point position, float angle){
	cv::Mat new_layer = cv::Mat::zeros(img_dst.size(), CV_8UC3);
	cv::Mat mask = Mask::Mask_rotated_rect(img_dst.size(), img_src.size(), position, angle);
	cv::Mat new_image = Mask::Rotation(img_src, angle);
	cv::Rect roi(position, new_image.size());
	new_image.copyTo(new_layer(roi));
	new_layer.copyTo(img_dst, mask);
}

cv::Mat Mask::Grab_zone(cv::Mat img_big, cv::Size roi_size, cv::Point position, float angle){
	cv::Mat result;
	cv::Mat warp_map = getRotationMatrix2D(position, angle, 1.0);
	cv::warpAffine(img_big, result, warp_map, img_big.size());
	cv::getRectSubPix(result, roi_size, position, result);
	return result;
}

cv::Mat Mask::Mask_rotated_rect(cv::Size big_size, cv::Size little_size, cv::Point position, float angle){
	cv::Mat mask = cv::Mat::zeros(big_size, CV_8UC3);
	cv::RotatedRect rotation_rect;
	rotation_rect.center = cv::Point(position.x + little_size.width, position.y + little_size.height);
	rotation_rect.angle = angle;
	rotation_rect.size = cv::Size(little_size.width - 2, little_size.height - 2);
	vector <cv::Point> poly_vertices, poly_roi;
	cv::Point2f rect_vertices[4];
	rotation_rect.points(rect_vertices);
	for(size_t i = 0; i < 4; i++){
		poly_vertices.push_back(rect_vertices[i]);
	}
	cv::approxPolyDP(poly_vertices, poly_roi, 1.0, true);
	cv::fillConvexPoly(mask, &poly_roi[0], poly_roi.size(), cv::Scalar(255, 255, 255), 8, 0);
	return mask;
}

cv::Mat Mask::Rotation(cv::Mat image, float angle){
	cv::Mat new_image;
	image.copyTo(new_image);
	cv::Point img_center(new_image.cols, new_image.rows);
	cv::Size new_size(new_image.cols * 2, new_image.rows * 2);
	cv::Mat mat_rot = cv::getRotationMatrix2D(img_center, -angle, 1.);
	cv::Mat mat_transl = cv::Mat(cv::Size(3, 2), CV_32FC1);
	mat_transl.at<float>(0, 0) = 1.; mat_transl.at<float>(0, 1) = 0.; mat_transl.at<float>(0, 2) = (float) new_image.cols / 2;
	mat_transl.at<float>(1, 0) = 0.; mat_transl.at<float>(1, 1) = 1.; mat_transl.at<float>(1, 2) = (float) new_image.rows / 2;
	cv::warpAffine(new_image, new_image, mat_transl, new_size);
	cv::warpAffine(new_image, new_image, mat_rot, new_size);
	return new_image;
}
