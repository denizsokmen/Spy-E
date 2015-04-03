

#ifndef SPYE_GUI_H
#define SPYE_GUI_H

#include "logic/System.h"

class Drawer;

class View;

class GUI : public System {

private:
    View *mainView;

public:
    Drawer *drawer;

    GUI(Drawer *drawer);

    void addSubview(View *view);


    void init();

    void update(float dt);

    void draw();

    void draw2D();
};


#endif //SPYE_GUI_H
