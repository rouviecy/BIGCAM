/*
 * @(#)		Share.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Shared data
 */

#ifndef SHARE
#define SHARE

#include <mutex>
#include <vector>
#include <map>
#include <iostream>

typedef std::map <std::string, float> FloatMap;
typedef std::map <std::string, float*> PFloatMap;
typedef std::vector <std::string> StringVec;

class Share{

public:

	Share();
	void Create_data(std::string key);
	void Send(PFloatMap input);
	FloatMap Receive(StringVec keys);

private:

	std::mutex mu;
	FloatMap data;

	void Lock();
	void Unlock();
};

#endif
