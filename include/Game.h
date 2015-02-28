#ifndef GAME_H_INC
#define GAME_H_INC

struct GLFWwindow;

class Scene;
class Input;
class Timer;

class Game {

private:
    Input* input;
    Scene* scene;
    float deltaTime;

public:
    bool init(int width, int height, char const *title, bool fullScreen);

    void setScene(Scene *scene);
    void removeScene();
    
    void update();
    void end();

    GLFWwindow *window;
    Timer *timer;
};


#endif