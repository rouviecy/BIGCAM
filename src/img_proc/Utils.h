/*
 * @(#)		Utils.h
 * @version	1.5
 * @autor	C. Rouvière
 */

/**
 * Outils divers et variés ...
 * 		- Dérivée du projet NAOSLAM https://github.com/rouviecy/NAO_SLAM/blob/master/Visio/cpp/src/Utils.h
 */

#ifndef UTILS
#define UTILS

#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

class Utils{

public:

	static int Distance_carree(int x1, int y1, int x2, int y2);
	static bool In_img(cv::Point pt, int max_x, int max_y);
	static std::vector <int> Rot2D(int x, int y, int theta);

};

#endif
