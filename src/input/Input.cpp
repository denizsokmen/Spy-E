/* 09/03/2015	-> switched from GLFW to SDL / arman	
*  09/03/2015	-> implemented eventQueue / arman 
*/

#include "input/Input.h"
#include <string>

Input::Input(SDL_Window *mainWindow) {
	this -> mainWindow = mainWindow;
	this -> keyState = new Uint32[SDL_NUM_SCANCODES];
}

void Input::update(float dt) {
	SDL_Event event;
	Event *tempEvent;
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
			tempEvent = new Event(event);
			std::string s = std::to_string(tempEvent->keyCode);
			printf(s.c_str());
			eventQueue.push(*tempEvent);
		}
	}
}
Input::~Input() {

}



