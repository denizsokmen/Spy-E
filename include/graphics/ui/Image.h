//
// Created by Taha Doğan Güneş on 02/04/15.
//

#ifndef SPYE_IMAGE_H
#define SPYE_IMAGE_H

#include <string>
#include <glm/glm.hpp>
#include <graphics/ui/View.h>

class Texture;

class Drawable;

class Image : public View {

private:
    Drawable *drawable;

public:

    Image(std::string name);
    Image(Texture *texture);

    ~Image();

    using View::draw;

    void draw();
};


#endif //SPYE_IMAGE_H