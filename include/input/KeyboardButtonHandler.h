#ifndef KEYBOARDBUTTONHANDLER_H_INC
#define KEYBOARDBUTTONHANDLER_H_INC

#include "SDL.h"
#include "input/ButtonHandler.h"
#include "input/Keyboard.h"
#include "input/Input.h"

class Input;

class KeyboardButtonHandler : public ButtonHandler {
private:
	Keyboard *keyboard;
public:
	bool isPressed();
	bool justPressed();
	void update();
	Input *input;
	KeyboardButtonHandler(Uint32, Input*);
	~KeyboardButtonHandler();
};

#endif
