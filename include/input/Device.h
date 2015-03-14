#ifndef DEVICE_H_INC
#define DEVICE_H_INC

#include "SDL.h"
#include <queue>

class Input;

class Device {
public:
	Input *input;
	virtual void update(SDL_Event &event) {}
	Device();
	~Device();
};

#endif
