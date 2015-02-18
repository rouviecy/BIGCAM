#include "Builder.h"

using namespace std;

Builder::Builder(){

}

void Builder::Retrieve_pictures(){
	this->list_img = io_file.Read();
}

void Builder::Build(){
	for(size_t i = 0; i < list_img.size(); i++){
		list_img[i].x_map = (int) ((float) list_img[i].img.rows * list_img[i].x / 10.);
		list_img[i].y_map = (int) ((float) list_img[i].img.cols * list_img[i].y / 10.);
	}
	int x_offset = list_img[0].x_map; int x_max = x_offset;
	int y_offset = list_img[0].y_map; int y_max = y_offset;
	for(size_t i = 0; i < list_img.size(); i++){
		if(x_offset > list_img[i].x_map){x_offset = list_img[i].x_map;}
		if(y_offset > list_img[i].y_map){y_offset = list_img[i].y_map;}
		if(list_img[i].x_map + list_img[i].img.cols > x_max){x_max = list_img[i].x_map + list_img[i].img.cols;}
		if(list_img[i].y_map + list_img[i].img.rows > y_max){y_max = list_img[i].y_map + list_img[i].img.rows;}
	}
	x_offset -= MARGIN_X / 2;
	y_offset -= MARGIN_Y / 2;
	cv::Mat bigmap = cv::Mat::zeros(y_max - y_offset + MARGIN_X / 2, x_max - x_offset + MARGIN_Y / 2, CV_8UC3);
	for(size_t i = 0; i < list_img.size(); i++){
		cv::Point position(list_img[i].x_map - x_offset, list_img[i].y_map - y_offset);
		Pick_and_place(list_img[i].img, bigmap, position, list_img[i].thz * 57.296);
	}
	cv::imwrite("test/map.png", bigmap);
}

void Builder::Pick_and_place(cv::Mat img_src, cv::Mat img_dst, cv::Point position, float angle){
	cv::Mat new_layer = cv::Mat::zeros(img_dst.size(), CV_8UC3);
	cv::Mat mask = Mask_rotated_rect(img_dst.size(), img_src.size(), position, angle);
	cv::Mat new_image = Rotation(img_src, angle);
	cv::Rect roi(position, new_image.size());
	new_image.copyTo(new_layer(roi));
	new_layer.copyTo(img_dst, mask);
}

cv::Mat Builder::Mask_rotated_rect(cv::Size big_size, cv::Size little_size, cv::Point position, float angle){
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

cv::Mat Builder::Rotation(cv::Mat image, float angle){
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
