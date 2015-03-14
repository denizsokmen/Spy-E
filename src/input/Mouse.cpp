#include "input/Mouse.h"

Mouse::Mouse(){
	this->buttonArray = new bool[SDL_NUM_SYSTEM_CURSORS];
	for (int i = 0; i < SDL_NUM_SYSTEM_CURSORS; i++)
		buttonArray[i] = false;
	this->mouseX = 0;
	this->mouseY = 0;
}

void Mouse::update(SDL_Event &event){
	SDL_GetMouseState(&mouseX, &mouseY);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		buttonArray[event.button.button] = true;
	else if (event.type == SDL_MOUSEBUTTONUP)
		buttonArray[event.button.button] = false;
}

Mouse::~Mouse(){
}