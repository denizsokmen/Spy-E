//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include <SDL_image.h>
#include "graphics/ui/Image.h"
#include "graphics/Texture.h"
#include "graphics/Drawable.h"
#include "graphics/Drawer.h"
#include <glm/glm.hpp>
#include <graphics/ui/GUI.h>


Image::Image() : View() {
    this->drawable = NULL;
}

Image::Image(std::string name) : View() {
    Texture *texture = new Texture();
    printf("[GUI] Loading image: %s \n", name.c_str());
    texture->createFromSDL(IMG_Load(name.c_str()));
    this->drawable = new Drawable(texture);
}

Image::Image(Texture *texture) : View() {
    this->drawable = new Drawable(texture);
}

void Image::draw() {
    View::draw();
    if (this->drawable != NULL) {
        glm::vec2 position(this->frame.x, this->frame.y);
        glm::vec2 size(this->frame.w, this->frame.h);
        GUI *gui = this->getSystem();
        Drawer *drawer = gui->drawer;
        drawer->draw(this->drawable, position, size);
    }
}

Image::~Image() {
    delete this->drawable;
}
