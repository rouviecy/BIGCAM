#include "Builder.h"

using namespace std;

Builder::Builder(){

}

void Builder::Retrieve_pictures(){
	this->list_img = io_file.Read();
}

void Builder::Build(){
	for(size_t i = 0; i < list_img.size(); i++){
		cv::Point img_center(list_img[i].img.cols, list_img[i].img.rows);
		cv::Mat mat_rot = cv::getRotationMatrix2D(img_center, - list_img[i].thz * 57.296, 1.);
		cv::Mat mat_transl = cv::Mat(cv::Size(3, 2), CV_32FC1);
		mat_transl.at<float>(0, 0) = 1.; mat_transl.at<float>(0, 1) = 0.; mat_transl.at<float>(0, 2) = (float) list_img[i].img.cols / 2;
		mat_transl.at<float>(1, 0) = 0.; mat_transl.at<float>(1, 1) = 1.; mat_transl.at<float>(1, 2) = (float) list_img[i].img.rows / 2;
		list_img[i].rotation_rect.center = img_center;
		list_img[i].rotation_rect.angle = list_img[i].thz * 57.296;
		list_img[i].rotation_rect.size = cv::Size(list_img[i].img.cols - 2, list_img[i].img.rows - 2);
		cv::Size new_size(list_img[i].img.cols * 2, list_img[i].img.rows * 2);
		cv::warpAffine(list_img[i].img, list_img[i].img, mat_transl, new_size);
		cv::warpAffine(list_img[i].img, list_img[i].img, mat_rot, new_size, CV_INTER_LINEAR);
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
	cv::Mat bigmap = cv::Mat::zeros(y_max - y_offset, x_max - x_offset, CV_8UC3);
	for(size_t i = 0; i < list_img.size(); i++){
		cv::Mat mask = cv::Mat::zeros(y_max - y_offset, x_max - x_offset, CV_8UC3);
		vector <cv::Point> poly_vertices, poly_roi;
		cv::Point2f rect_vertices[4];
		list_img[i].rotation_rect.points(rect_vertices);
		for(size_t j = 0; j < 4; j++){
			poly_vertices.push_back(cv::Point(list_img[i].x_map - x_offset + rect_vertices[j].x, list_img[i].y_map - y_offset + rect_vertices[j].y));
		}
		cv::approxPolyDP(poly_vertices, poly_roi, 1.0, true);
		cv::fillConvexPoly(mask, &poly_roi[0], poly_roi.size(), cv::Scalar(255, 255, 255), 8, 0);
		cv::Mat new_layer = cv::Mat::zeros(y_max - y_offset, x_max - x_offset, CV_8UC3);
		cv::Rect roi(cv::Point(list_img[i].x_map - x_offset, list_img[i].y_map - y_offset), list_img[i].img.size());
		list_img[i].img.copyTo(new_layer(roi));
		new_layer.copyTo(bigmap, mask);
	}
	cv::imwrite("test/map.png", bigmap);

}
