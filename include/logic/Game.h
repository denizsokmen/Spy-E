#ifndef GAME_H_INC
#define GAME_H_INC

#include "SystemController.h"
#include "SDL.h"

struct GLFWwindow;

class Scene;
class Input;
class Timer;
class SystemController;

class Game {

private:
public:
    SystemController *getController() const {
        return controller;
    }

    void setController(SystemController *controller) {
        this->controller = controller;
    }

private:
    SystemController* controller;
    unsigned long deltaTime;

public:
	bool quit;
    bool init(int width, int height, char const *title, bool fullScreen);
    
    void update();
    void end();

    GLFWwindow *window;
    Timer *timer;
    Scene *scene;
    Input *input;
    SDL_Window *mainWindow;
    SDL_GLContext mainGLContext;
};


#endif