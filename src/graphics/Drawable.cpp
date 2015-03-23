//
// Created by deniz on 21/03/15.
//

#include <graphics/Texture.h>
#include "graphics/Drawable.h"

Texture *Drawable::getTexture() {
    return texture;
}

Drawable::Drawable(Texture* tex) {
    texture = tex;
}
