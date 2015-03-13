#include "input/ButtonHandler.h"

ButtonHandler::ButtonHandler(Uint32 keyCode, Input *input){
	this->pressFlag = false;
	this->keyCode = keyCode;
	this->input = input;
}

void ButtonHandler::setKeyCode(Uint32 keyCode){
	this->keyCode = keyCode;
}

Uint32 ButtonHandler::getKeyCode(){
	return this->keyCode;
}

void ButtonHandler::setPressFlag(bool flag){
	this->pressFlag = flag;
}

bool ButtonHandler::getPressFlag() {
	return this->pressFlag;
}

ButtonHandler::~ButtonHandler(){

}