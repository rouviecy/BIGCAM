#include "Builder.h"

using namespace std;

Builder::Builder(){
	last_position = cv::Point(0, 0);
}

void Builder::Retrieve_pictures(){
	this->list_img = io_file.Read();
}

void Builder::Build(){
	for(size_t i = 0; i < list_img.size(); i++){
		list_img[i].x_map = (int) ((float) list_img[i].x * 600.);
		list_img[i].y_map = (int) ((float) list_img[i].y * 600.);
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
		if(last_position == position){continue;}
		last_position = position;
		Mask::Pick_and_place(list_img[i].img, bigmap, position, list_img[i].thz * 57.296);
		tracking.Set_img_next(list_img[i].img);
		if(i > 0){
			tracking.Set_img_prev(list_img[i - 1].img);
			tracking.GoodFeatures(50);
			struct_link_amers new_link;
			if(tracking.Tracker()){
				tracking.Flot_optique();
				new_link.amers_prev = tracking.Get_amers();
				new_link.amers_next = tracking.Get_nv();
				new_link.x_origin_prev = list_img[i - 1].x_map - x_offset + list_img[i - 1].img.cols / 2;
				new_link.y_origin_prev = list_img[i - 1].y_map - y_offset + list_img[i - 1].img.rows / 2;
				new_link.thz_origin_prev = list_img[i - 1].thz;
				new_link.x_origin_next = list_img[i].x_map - x_offset + list_img[i].img.cols / 2;
				new_link.y_origin_next = list_img[i].y_map - y_offset + list_img[i].img.rows / 2;
				new_link.thz_origin_next = list_img[i].thz;
				amers.push_back(new_link);
			}
		}
	}
	for(size_t i = 0; i < amers.size(); i++){
		for(size_t j = 0; j < amers[i].amers_next.size(); j++){
			// TODO : corriger erreur de formule ... peut-être cos() * (truc + ???)
			int x1 = amers[i].x_origin_prev + (int) ((float) +cos(amers[i].thz_origin_prev) * (float) amers[i].amers_prev[j].x + (float) -sin(amers[i].thz_origin_prev) * (float) amers[i].amers_prev[j].y);
			int y1 = amers[i].y_origin_prev + (int) ((float) +sin(amers[i].thz_origin_prev) * (float) amers[i].amers_prev[j].x + (float) +cos(amers[i].thz_origin_prev) * (float) amers[i].amers_prev[j].y);
			int x2 = amers[i].x_origin_next + (int) ((float) +cos(amers[i].thz_origin_next) * (float) amers[i].amers_next[j].x + (float) -sin(amers[i].thz_origin_next) * (float) amers[i].amers_next[j].y);
			int y2 = amers[i].y_origin_next + (int) ((float) +sin(amers[i].thz_origin_next) * (float) amers[i].amers_next[j].x + (float) +cos(amers[i].thz_origin_next) * (float) amers[i].amers_next[j].y);
//			cv::line(bigmap, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255), 1);
		}
	}
	cv::imwrite("test/map.png", bigmap);
}
