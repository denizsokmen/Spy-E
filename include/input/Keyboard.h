#ifndef KEYBOARD_H_INC
#define KEYBOARD_H_INC

#include "SDL.h"
#include "input/Device.h"

class Keyboard : public Device{

public:
	int keyCode;
	bool *keyArray;
	void update(SDL_Event &event);
	Keyboard();
	~Keyboard();

};
#endif
