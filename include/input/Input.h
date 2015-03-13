#ifndef INPUT_H_INC
#define INPUT_H_INC

#include <iostream>
#include "logic/System.h"
#include "input/Device.h"
#include "SDL.h"
#include <queue>
#include <list>

class Input : public System {

public:
	std::list<Device*> deviceList;
	SDL_Window *mainWindow;
	std::queue<SDL_Event> eventQueue;
	void initDeviceList();
	void updateDevices(SDL_Event event);
	void cleanQueue();
	void update(float dt);
    Input(SDL_Window *mainWindow);
    ~Input();
};

#endif