#include <stdlib.h>
#include <SDL/SDL.h>
#include <unistd.h>
#include <queue>
#include <iostream>

#ifndef JOYSTICK
#define JOYSTICK

class Joystick{

public:

	Joystick();
	~Joystick();
	bool Connect_joystick(int num_device);
	void Disconnect_joystick();

	void Update_event();
	void Print_infos();

	int Get_nb_buttons();
	int Get_nb_axes();
	int Get_nb_hats();
	int *Get_buttons();
	int *Get_axes();
	int *Get_hats();
	std::queue<char> Get_keys();

private:

	SDL_Event event;
	SDL_Surface *screen;
	SDL_Joystick *joystick;
	int num_device;
	int nb_buttons,	nb_axes,	nb_hats;
	int *buttons,	*axes,		*hats;
	std::queue<char> keys;

};

#endif
