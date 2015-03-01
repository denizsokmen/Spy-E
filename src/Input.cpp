#include "Input.h"



Input::Input(GLFWwindow *window) {
	this -> window = window;
	this -> keyState = NULL;
}

void Input::update(float dt) {

}

GLFWkeyfun Input::glfwSetKeyCallback(GLFWwindow *window, GLFWkeyfun cbfun){
	std::cout << ("%d\n", cbfun);
	return cbfun;
}

Input::~Input() {

}



