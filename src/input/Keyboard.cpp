#include "input/Keyboard.h"

Keyboard::Keyboard(){
	keyArray = new bool[SDL_NUM_SCANCODES];
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		keyArray[i] = false;	
}

void Keyboard::update(SDL_Event &event){
	int keyCode;
	if (event.key.keysym.scancode < 512 && event.key.keysym.scancode >= 0)
		keyCode = event.key.keysym.scancode;
	else
		keyCode = SDL_GetKeyFromScancode(event.key.keysym.scancode);
	if (event.type == SDL_KEYUP)
		keyArray[keyCode] = false;
	else if (event.type == SDL_KEYDOWN) {
		keyArray[keyCode] = true;
	}

}

Keyboard::~Keyboard(){
}