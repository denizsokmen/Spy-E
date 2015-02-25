#ifndef GAME_H_INC
#define GAME_H_INC

class GLFWwindow;

class Game {

public:
    bool init(int width, int height, char const *title, bool fullscreen);
    void update();
    void end();

    GLFWwindow *window;

};


#endif