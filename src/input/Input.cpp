#include "input/Input.h"
#include "input/Keyboard.h"


Input::Input(SDL_Window *mainWindow) {
	this->mainWindow = mainWindow;
	initDeviceList();
}

void Input::initDeviceList(){
	Keyboard *keyboard = new Keyboard();
	this->deviceList.push_back(keyboard);
}

void Input::update(float dt) {
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		eventQueue.push(event);
		switch (event.type){
		case SDL_WINDOWEVENT:
			printf("windowevent");
		default:
			printf("event");
		}
	}
	cleanQueue();
}

void Input::cleanQueue() {
	while (!eventQueue.empty())
		eventQueue.pop();
}

Input::~Input() {

}



