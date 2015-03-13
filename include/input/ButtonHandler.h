#ifndef BUTTONHANDLER_H_INC
#define BUTTONHANDLER_H_INC

#include "SDL.h"
#include "input/Keyboard.h"

class ButtonHandler {
private:
	bool pressFlag;
	int keyCode;

public:
	Input *input;

	virtual void update();
	virtual bool isPressed() { return false; }
	virtual bool justPressed();
	virtual bool wasReleased();
	void setKeyCode(int);
	int getKeyCode();
	void setPressFlag(bool);
	bool getPressFlag();

	ButtonHandler(int, Input*);
	~ButtonHandler();

	bool firstPress;
	bool currentlyPressed;
};

#endif
