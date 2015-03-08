#ifndef INPUT_H_INC
#define INPUT_H_INC

#include <iostream>
#include "System.h"
#include "SDL.h"
#include <queue>

class Input : public System {

public:
	SDL_Window *mainWindow;
	std::queue<int> eventQueue;
	bool *keyState;

	void update();
    Input(SDL_Window *mainWindow);
    ~Input();
    

};

#endif