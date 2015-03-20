
#include "input/Mouse.h"
#include "SDL.h"

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



void Mouse::setPosition(int mouseX, int mouseY, SDL_Window *mainWindow) {
	SDL_WarpMouseInWindow(mainWindow, mouseX, mouseY);
}
