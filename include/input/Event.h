#ifndef EVENT_H_INC
#define EVENT_H_INC

#include "SDL.h"
#include <SDL_events.h>

#define NONE		-1
#define KEYPRESS	0
#define KEYRELEASE	1

class Event {
public:
	int keyCode;
	int keyPress;
	Event(SDL_Event sdlEvent);
	~Event();
	
};


#endif
