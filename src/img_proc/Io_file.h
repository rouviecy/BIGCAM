/*
 * @(#)		Io_file.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Read-write images with metadata
 */

#ifndef IO_FILE
#define IO_FILE

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <fstream>

typedef struct{
	cv::Mat img;
	std::string path;
	int number;
	float x;
	float y;
	float z;
} struct_img;

class Io_file{

public:

	Io_file();
	~Io_file();
	void Write(struct_img message);
	void Clear_log();

private:

	#define LOG_PATH "test/log.txt"
	const char* log_path;
	std::ofstream log_out;

};

#endif
