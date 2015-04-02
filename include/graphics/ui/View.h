//
// Created by Taha Doğan Güneş on 02/04/15.
//

#ifndef SPYE_VIEW_H
#define SPYE_VIEW_H

#include <glm/glm.hpp>
#include <vector>
#include "graphics/ui/Primitives.h"


class Image;

class View {

public:
    std::vector<View *> subViews;
    Rect frame = Rect(0, 0, 0, 0);
    Color color = Color(0, 0, 0);
    Image *backgroundImage;


    void addSubview(View *view);
};


#endif //SPYE_VIEW_H
