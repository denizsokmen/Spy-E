#include "input/KeyboardButtonHandler.h"

KeyboardButtonHandler::KeyboardButtonHandler(Uint32 keycode, Input *input)
	: ButtonHandler(keycode, input) {
	this->keyboard = input->getKeyboard();
}

void KeyboardButtonHandler::update(){
	if (keyboard->keyArray[this->getKeyCode()])
		this->setPressFlag(true);
	else
		this->setPressFlag(false);
}

bool KeyboardButtonHandler::justPressed(){
	return this->getPressFlag();
}

bool KeyboardButtonHandler::isPressed(){
	return keyboard->keyArray[this->getKeyCode()];
}

KeyboardButtonHandler::~KeyboardButtonHandler(){

}