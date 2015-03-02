#ifndef GAME_H_INC
#define GAME_H_INC

struct GLFWwindow;

class Scene;
class Input;
class Timer;
class SystemController;

class Game {

private:
    SystemController* controller;
    float deltaTime;

public:
    bool init(int width, int height, char const *title, bool fullScreen);
    
    void update();
    void end();

    GLFWwindow *window;
    Timer *timer;
};


#endif