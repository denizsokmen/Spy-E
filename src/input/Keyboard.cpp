#include "input/Keyboard.h"

Keyboard::Keyboard(){
	keyArray = new bool[SDL_NUM_SCANCODES];
}

void Keyboard::update(SDL_Event event){
	if (event.type == SDL_KEYUP)
		keyArray[event.key.keysym.scancode] = true;
	else if (event.type == SDL_KEYDOWN) 
		keyArray[event.key.keysym.scancode] = false;
}

Keyboard::~Keyboard(){

}