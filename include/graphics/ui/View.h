
#ifndef SPYE_VIEW_H
#define SPYE_VIEW_H

#include <glm/glm.hpp>
#include <vector>
#include "graphics/ui/Primitives.h"

class GUI;

class Image;


class View {

private:
    GUI *system;

public:
    std::vector<View *> subViews;
    Rect frame = Rect(0, 0, 0, 0);
    Color color = Color(0, 0, 0);
    Image *backgroundImage;

    GUI *getSystem();

    void setSystem(GUI *system);

    void addSubview(View *view);

    virtual void draw();
};


#endif //SPYE_VIEW_H
