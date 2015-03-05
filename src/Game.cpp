
#include <stdio.h>
#include <GL/glew.h>
#include <glfw3.h>
#include <SDL.h>
#include "Timer.h"
#include "Scene.h"
#include "Renderer.h"
#include "Input.h"
#include "Game.h"
#include "SystemController.h"
#define TICK_PER_SECOND 100

bool Game::init(int width, int height, char const *title, bool fullScreen) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) ;
    SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 ) ;

    mainWindow = SDL_CreateWindow("Spy-E", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, ((fullScreen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN) |SDL_WINDOW_OPENGL);
    mainGLContext = SDL_GL_CreateContext(mainWindow);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    scene = new Scene();
    input = new Input(window);

    controller = new SystemController();
    controller->addCoreSystem(input);
    controller->addCoreSystem(scene);

    timer = new Timer(TICK_PER_SECOND);

    return true;
}

void Game::update() {
    unsigned long lastTime = SDL_GetTicks();
    int tickCount = 0;
    bool isUpdated = false;
    SDL_Event event;
    bool quit = false;
    while(!quit) {
        /* TODO: polled events should be handled by Input*/
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit=true;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;

            }
        }
        unsigned long currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;


        while (timer->tick()) {
            controller->update(timer->getTickSize());
            tickCount++;
            isUpdated = true;
        }
        timer->endLoop();

        if (isUpdated)
            controller->draw();

        isUpdated = false;
        if (deltaTime > 1000) {
            lastTime = currentTime;
            printf("%d tick %d\n", tickCount, SDL_GetTicks());
        }

        SDL_GL_SwapWindow(mainWindow);

    }
}

void Game::end() {
    SDL_GL_DeleteContext(mainGLContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

