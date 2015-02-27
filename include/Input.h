#ifndef INPUT_H_INC
#define INPUT_H_INC

#include <glfw3.h>
#include <iostream>


class Input {

public:
	bool *keyState;
	GLFWwindow *window;

    Input(GLFWwindow *window);
    ~Input();
    void update();
	GLFWkeyfun glfwSetKeyCallback(GLFWwindow *window, GLFWkeyfun cbfun);
};

#endif