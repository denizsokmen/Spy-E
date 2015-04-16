

#ifndef SPYE_GUI_H
#define SPYE_GUI_H

#include "logic/System.h"
#include "input/Input.h"
#include <string>

class Drawer;
class Font;
class View;

class GUI : public System {

public:
    View* mainView;
    Font* font;
    Drawer* drawer;
    Input* input;

    GUI(Drawer* drawer);
    GUI(Drawer* drawer, Input* input);

    ~GUI();
    void addSubview(View* view);
    View* viewWithTag(std::string tag);
    void init();
    void update(float dt);
    void draw();
    void draw2D();
    Input* getInput();
};


#endif //SPYE_GUI_H
