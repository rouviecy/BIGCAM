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
		Mask::Pick_and_place(list_img[i].img, bigmap, position, list_img[i].thz * 57.296);
	}
	cv::imwrite("test/map.png", bigmap);
}
