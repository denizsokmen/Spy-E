//
// Created by Deniz Sokmen on 17/03/15.
//

#include <SDL_image.h>
#include "graphics/Texture.h"


void Texture::createFromSDL(SDL_Surface *surface) {
    if (surface == NULL) {
        printf("Texture not found\n");
        return;
    }


    id = 0;
	width = surface->w;
	height = surface->h;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    GLenum mode = GL_RGB;

    if(surface->format->BytesPerPixel == 4) {
        mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   // glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(GLuint unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);

}