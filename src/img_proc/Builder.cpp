#include "Builder.h"

using namespace std;

Builder::Builder(){

}

void Builder::Retrieve_pictures(){
	this->list_img = io_file.Read();
}

void Builder::Build(){
	for(size_t i = 0; i < list_img.size(); i++){
		list_img[i].x_map = (int) ((float) list_img[i].img.rows * list_img[i].x / 2.);
		list_img[i].y_map = (int) ((float) list_img[i].img.cols * list_img[i].y / 2.);
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
		cv::Rect roi(cv::Point(list_img[i].x_map - x_offset, list_img[i].y_map - y_offset), list_img[i].img.size());
		list_img[i].img.copyTo(bigmap(roi));
	}
	cv::imwrite("test/map.png", bigmap);
}
