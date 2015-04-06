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
    Image();
    Image(std::string name);
    Image(Texture *texture);
    ~Image();

    void setTexture(Texture *texture);

    void draw();
};


#endif //SPYE_IMAGE_H
