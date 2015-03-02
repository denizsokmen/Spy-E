
#include <stdio.h>
#include <GL/glew.h>
#include <glfw3.h>
#include "Timer.h"
#include "Scene.h"
#include "Renderer.h"
#include "Input.h"
#include "Game.h"
#include "SystemController.h"
#define TICK_PER_SECOND 400

bool Game::init(int width, int height, char const *title, bool fullScreen) {
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow( width, height, title, fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
    if( window == NULL ) {
        fprintf( stderr, "Failed to open GLFW window.");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    controller = new SystemController();
    controller->addCoreSystem(new Input(window));
    controller->addCoreSystem(new Scene());

    timer = new Timer(TICK_PER_SECOND);

    return true;
}

void Game::update() {
    double lastTime = glfwGetTime();
    int tickCount = 0;
	do {
        double currentTime = glfwGetTime();
        deltaTime = float(currentTime - lastTime);


        while (timer->tick()) {
            controller->update(timer->getTickSize());
            tickCount++;
        }


        timer->endLoop();
        controller->draw();
        
		glfwSwapBuffers(window);
		glfwPollEvents();

        if (deltaTime > 1.0) {
            lastTime = currentTime;
            printf("%d tick \n", tickCount);
        }

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}

void Game::end() {
    glfwTerminate();
}

