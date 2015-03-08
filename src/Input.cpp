/* 09/03/2015	-> switched from GLFW to SDL / arman	*/

#include "Input.h"

Input::Input(SDL_Window *mainWindow) {
	this-> mainWindow = mainWindow;
	this-> keyState = new bool[SDL_NUM_SCANCODES];
}

void Input::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
				//TODO: add cases
			default:
				keyState[event.key.keysym.scancode] = false;
			}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				//TODO: add cases
			default:
				keyState[event.key.keysym.scancode] = true;
				break;
			}
			break;
		default:
			break;
		}
	}
}
Input::~Input() {

}



