#include "input/Input.h"


Input::Input(SDL_Window *mainWindow) {
	this->mainWindow = mainWindow;
	initDeviceList();
}

void Input::initDeviceList(){
	this->keyboard = new Keyboard();
	this->mouse = new Mouse();
	this->deviceList.push_back(keyboard);
	this->deviceList.push_back(mouse);
}

void Input::update(float dt) {
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		eventQueue.push(event);
		switch (event.type){
		case SDL_WINDOWEVENT:
			printf("");
		default:
			updateDevices(event);
			updateHandlers();
			printf("");
		}
	}
	cleanQueue();
}

void Input::updateDevices(SDL_Event &event) {
	for (auto it = deviceList.begin(); it != deviceList.end(); ++it){
		(*it)->update(event);
	}
}

void Input::updateHandlers(){
	for (auto it = buttonMap.begin(); it != buttonMap.end(); ++it){
		it->second->update();
	}
}

void Input::mapButton(std::string key, ButtonHandler *buttonHandler){
	this->buttonMap[key] = buttonHandler;
}

bool Input::justPressed(std::string buttonKey){
	auto it = this->buttonMap.find(buttonKey);
	if (it != buttonMap.end()) {
		return it->second->justPressed();
	}
	return false;
}

bool Input::wasReleased(std::string buttonKey) {
	auto it = this->buttonMap.find(buttonKey);
	if (it != buttonMap.end()) 
		return it->second->wasReleased();
	return false;
}

bool Input::isPressed(std::string buttonKey){
	auto it = this->buttonMap.find(buttonKey);
	if (it != buttonMap.end())
		return it->second->isPressed();
	return false;
}

Keyboard* Input::getKeyboard(){
	return this->keyboard;
}

Mouse* Input::getMouse(){
	return this->mouse;
}

void Input::cleanQueue() {
	while (!eventQueue.empty())
		eventQueue.pop();
}

Input::~Input() {

}



