#ifndef GAME_H_INC
#define GAME_H_INC

struct GLFWwindow;

class Scene;
class Input;

class Game {

private:
    Input* input;
    Scene* scene;


public:
    bool init(int width, int height, char const *title, bool fullScreen);

    void setScene(Scene *scene);
    void removeScene();

    void update();
    void end();

    GLFWwindow *window;

};


#endif