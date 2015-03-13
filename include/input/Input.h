#ifndef INPUT_H_INC
#define INPUT_H_INC

#include <iostream>
#include "logic/System.h"
#include "input/Device.h"
#include "input/ButtonHandler.h"
#include "SDL.h"
#include <queue>
#include <list>
#include <map>

class Device;

class Input : public System {

public:
	std::map<std::string, ButtonHandler*> buttonMap;
	std::list<Device*> deviceList; 
	SDL_Window *mainWindow;
	std::queue<SDL_Event> eventQueue;
	Keyboard* keyboard;

	Keyboard* getKeyboard();
	
	bool justPressed(std::string);
	bool isPressed(std::string);
	bool wasReleased(std::string buttonKey);

	void mapButton(std::string, ButtonHandler*);

	void initDeviceList();
	void updateDevices(SDL_Event &event);
	void updateHandlers();

	void cleanQueue();
	void update(float dt);

    Input(SDL_Window *mainWindow);
    ~Input();

};

#endif