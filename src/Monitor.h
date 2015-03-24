/*
 * @(#)		Monitor.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Show robot state in a GUI
 */

#ifndef MONITOR
#define MONITOR

#include <cmath>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "stereotypes/ComThread.h"
#include "utils/Serial.h"

class Monitor : public ComThread{

public:

	Monitor();
	~Monitor();
	void Set_serial_port(int serial_port);

private:

	#define MONITOR_SIZE	700
	#define MONITOR_BORDER	100

	float	x,		y,		z;
	float	thx,	thy,	thz;

	float	min_coord, max_coord;

	int serial_port;
	SDL_Window *window;
	SDL_Renderer* render;
	TTF_Font* font;
	std::vector <std::vector <float> > path;

	void Job();
	void IO();
	void Draw_monitor();
	void Draw_text(std::string txt, SDL_Color color, int x, int y);

};

#endif
