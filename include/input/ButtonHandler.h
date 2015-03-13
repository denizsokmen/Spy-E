#ifndef BUTTONHANDLER_H_INC
#define BUTTONHANDLER_H_INC

#include "SDL.h"
#include "input/Keyboard.h"

class ButtonHandler {
private:
	bool pressFlag;
	Uint32 keyCode;

public:
	Input *input;

	virtual void update() {}
	virtual bool isPressed() { return false; }
	virtual bool justPressed() { return false; }
	void setKeyCode(Uint32);
	Uint32 getKeyCode();
	void setPressFlag(bool);
	bool getPressFlag();

	ButtonHandler(Uint32, Input*);
	~ButtonHandler();
};

#endif
