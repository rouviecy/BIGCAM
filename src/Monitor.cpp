#include "Monitor.h"

using namespace std;

Monitor::Monitor() : ComThread(){
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("Monitor", 0, 0, MONITOR_SIZE, MONITOR_SIZE, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	font = TTF_OpenFont("arial.ttf", 10);
	const char * error = TTF_GetError();
	cout << error << endl;
	min_coord = -1.;
	max_coord = +1.;
}

Monitor::~Monitor(){
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Monitor::IO(){

}

void Monitor::Job(){
	Critical_receive();
	Draw_monitor();
}

void Monitor::Draw_monitor(){
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	vector <float> xy; xy.push_back(x); xy.push_back(y); 
	path.push_back(xy);
	if		(x < min_coord)	{min_coord = x;}
	else if	(x > max_coord)	{max_coord = x;}
	if		(y < min_coord)	{min_coord = y;}
	else if	(y > max_coord)	{max_coord = y;}
	int draw_prev_x, draw_prev_y;
	SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
	for(size_t i = 0; i < path.size(); i++){
		int draw_x = MONITOR_BORDER / 2 + (int) ((float) (MONITOR_SIZE - MONITOR_BORDER) * ((float) path[i][0] - min_coord) / (max_coord - min_coord));
		int draw_y = MONITOR_BORDER / 2 + (int) ((float) (MONITOR_SIZE - MONITOR_BORDER) * ((float) path[i][1] - min_coord) / (max_coord - min_coord));
		if(i != 0){
			SDL_RenderDrawLine(render, draw_prev_x, draw_prev_y, draw_x, draw_y);
		}
		SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
		draw_prev_x = draw_x;
		draw_prev_y = draw_y;
		if(i == path.size() - 1){
//			ellipseRGBA(render, 20, 20, draw_x, draw_y);
			int arrow_x = draw_x + 40 * cos(thz);
			int arrow_y = draw_y + 40 * sin(thz);
			int arrow_l_x = arrow_x + 10 * cos(thz + 2.5);
			int arrow_l_y = arrow_y + 10 * sin(thz + 2.5);
			int arrow_r_x = arrow_x + 10 * cos(thz - 2.5);
			int arrow_r_y = arrow_y + 10 * sin(thz - 2.5);
			SDL_RenderDrawLine(render, draw_x, draw_y, arrow_x, arrow_y);
			SDL_RenderDrawLine(render, arrow_l_x, arrow_l_y, arrow_x, arrow_y);
			SDL_RenderDrawLine(render, arrow_r_x, arrow_r_y, arrow_x, arrow_y);
		}
	}
	SDL_Color red = {255, 0, 0};
	Draw_text("x = " + to_string(x), red, 10, 20);
	Draw_text("y = " + to_string(y), red, 10, 40);
	Draw_text("z = " + to_string(z), red, 10, 60);
	SDL_RenderPresent(render);
}

void Monitor::Draw_text(string txt, SDL_Color color, int x, int y){
	SDL_Surface* surface = TTF_RenderText_Solid(font, txt.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
	int w = 0; int h = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect renderQuad = {x, y, w, h};
	SDL_RenderCopy(render, texture, NULL, &renderQuad);
	SDL_DestroyTexture(texture);
}

void Monitor::Set_serial_port(int serial_port){this->serial_port = serial_port;}
