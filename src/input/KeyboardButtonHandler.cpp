#include "input/KeyboardButtonHandler.h"

KeyboardButtonHandler::KeyboardButtonHandler(Uint32 keycode, Input *input)
	: ButtonHandler(keycode, input) {
	this->keyboard = input->getKeyboard();
}


bool KeyboardButtonHandler::isPressed(){
	return keyboard->keyArray[this->getKeyCode()];
}

KeyboardButtonHandler::~KeyboardButtonHandler(){

}