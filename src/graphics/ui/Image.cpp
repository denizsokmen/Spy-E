//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include <SDL_image.h>
#include "graphics/ui/Image.h"
#include "graphics/Texture.h"
#include "graphics/Drawable.h"


Image::Image(std::string name) {
    Texture *texture = new Texture();
    texture->createFromSDL(IMG_Load(name.c_str()));
    this->drawable = new Drawable(texture);
}

Image::Image(Texture *texture) {
    this->drawable = new Drawable(texture);
}

Image::~Image() {
    delete this->drawable;
}
