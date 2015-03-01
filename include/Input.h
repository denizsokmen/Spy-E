#ifndef INPUT_H_INC
#define INPUT_H_INC

#include <glfw3.h>
#include <iostream>
#include "System.h"

class Input : public System {

public:
	bool *keyState;
	GLFWwindow *window;

    Input(GLFWwindow *window);
    ~Input();
    void update(float dt);
	GLFWkeyfun glfwSetKeyCallback(GLFWwindow *window, GLFWkeyfun cbfun);
};

#endif