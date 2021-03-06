#ifndef GAME_H_INC
#define GAME_H_INC

#include "SystemController.h"
#include "SDL.h"

struct GLFWwindow;

class Scene;
class Input;

class Timer;
class SystemController;
class Drawer;
class Physics;
class GUI;

class Sounds;
class Game {

private:
public:
    Game();

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
    int width;
    int height;
    void update();
    void end();

    float fps;

    GLFWwindow *window;
    Timer *timer;
    Scene *scene;
    Input *input;
    Sounds *sounds;

    SDL_Window *mainWindow;
    SDL_GLContext mainGLContext;
    GUI *gui;
    Drawer *drawer;
    Physics *physics;

    void initDebugOverlay() const;
};


#endif