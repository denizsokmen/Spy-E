#include "input/MouseButtonHandler.h"

MouseButtonHandler::MouseButtonHandler(int keycode, Input *input)
: ButtonHandler(keycode, input) {
	this->mouse = input->getMouse();
}


bool MouseButtonHandler::isPressed(){
	return mouse->buttonArray[this->getKeyCode()];
}

MouseButtonHandler::~MouseButtonHandler(){

}