#include <stdlib.h>
#include <SDL2/SDL.h>
#include <unistd.h>
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

private:

	SDL_Event event;
	SDL_Joystick *joystick;
	int num_device;
	int nb_buttons,	nb_axes,	nb_hats;
	int *buttons,	*axes,		*hats;

};

#endif
