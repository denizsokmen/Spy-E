#include "input/Event.h"

Event::Event(SDL_Event sdlEvent) {
	if (sdlEvent.type == SDL_KEYDOWN)
		this->keyPress = KEYPRESS;
	else if (sdlEvent.type == SDL_KEYUP)
		this->keyPress = KEYRELEASE;
	else
		this->keyPress = NONE;

	this->keyCode = sdlEvent.key.keysym.scancode;
}

Event::~Event(){

}
