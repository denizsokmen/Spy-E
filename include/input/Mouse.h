#ifndef MOUSE_H_INC
#define MOUSE_H_INC

#include "SDL.h"
#include "input/Device.h"

class Mouse : public Device{

public:
	bool *buttonArray;
	int mouseX;
	int mouseY;
	void update(SDL_Event &event);
	Mouse();
	~Mouse();

};
#endif
