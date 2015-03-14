#ifndef MOUSEBUTTONHANDLER_H_INC
#define MOUSEBUTTONHANDLER_H_INC

#include "SDL.h"
#include "input/ButtonHandler.h"
#include "input/Mouse.h"
#include "input/Input.h"

class Input;

class MouseButtonHandler : public ButtonHandler {
private:
	Mouse *mouse;
public:
	bool isPressed();
	Input *input;
	MouseButtonHandler(int, Input*);
	~MouseButtonHandler();
};

#endif
