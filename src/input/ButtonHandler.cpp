#include "input/ButtonHandler.h"

ButtonHandler::ButtonHandler(int keyCode, Input *input){
	currentlyPressed = false;
	firstPress = false;
	this->keyCode = keyCode;
	this->input = input;
}

void ButtonHandler::setKeyCode(int keyCode){
	this->keyCode = keyCode;
}

int ButtonHandler::getKeyCode(){
	return this->keyCode;
}

ButtonHandler::~ButtonHandler(){

}

bool ButtonHandler::justPressed() {
	if (!firstPress && isPressed()) {
		firstPress = true;
		return true;
	}
	return false;
}

bool ButtonHandler::wasReleased() {
	if (currentlyPressed && !isPressed()) {
		currentlyPressed = false;
		return true;
	}

	return false;
}

void ButtonHandler::update() {
	if (!isPressed())
		firstPress = false;
	else
		currentlyPressed = true;
}
