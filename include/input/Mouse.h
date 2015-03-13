#ifndef MOUSE_H_INC
#define MOUSE_H_INC

#include "SDL.h"
#include "input/Device.h"

class Mouse : public Device{

public:
	bool *keyArray;
	void update(SDL_Event &event);
	Mouse();
	~Mouse();

};
#endif
