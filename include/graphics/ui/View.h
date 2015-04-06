
#ifndef SPYE_VIEW_H
#define SPYE_VIEW_H

#include <glm/glm.hpp>
#include <vector>
#include "graphics/ui/Primitives.h"

class GUI;

class Image;


class View {

protected:
    Rect frame = Rect(0, 0, 0, 0);

private:
    GUI *system;

public:
    View();

    ~View();
    std::vector<View *> subViews;
    Color color = Color(0, 0, 0);
    Image *backgroundImage;
    GUI *getSystem();



    virtual void addSubview(View *view);
    virtual void setSystem(GUI *system);
    virtual void setFrame(Rect frame);
    virtual void draw();
};


#endif //SPYE_VIEW_H
