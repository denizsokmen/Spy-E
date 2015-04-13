
#ifndef SPYE_VIEW_H
#define SPYE_VIEW_H

#include "graphics/ui/Primitives.h"
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>


class GUI;

class Image;


class View {

protected:
    Rect frame = Rect(0, 0, 0, 0);

private:
    GUI *system;
    std::map<std::string, View*> viewMap;
    std::string tag;


public:
    bool hidden;
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
    virtual void setTag(std::string tag);
    virtual std::string getTag();
    virtual View *viewWithTag(std::string tag);

};


#endif //SPYE_VIEW_H
