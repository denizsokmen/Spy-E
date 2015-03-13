#include "input/Input.h"


Input::Input(SDL_Window *mainWindow) {
	this->mainWindow = mainWindow;
	initDeviceList();
}

void Input::initDeviceList(){
	this->keyboard = new Keyboard();
	this->deviceList.push_back(keyboard);
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

bool Input::justPressed(std::string buttonKey){
	auto it = this->buttonMap.find(buttonKey);
	if (it != buttonMap.end()) {
		it->second->justPressed();
	}
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

void Input::updateHandlers(){
	for (auto it = buttonMap.begin(); it != buttonMap.end(); ++it){
		it->second->update();
	}
}

void Input::mapButton(std::string key, ButtonHandler *buttonHandler){
	this->buttonMap[key] = buttonHandler;
}

void Input::cleanQueue() {
	while (!eventQueue.empty())
		eventQueue.pop();
}


Input::~Input() {

}



