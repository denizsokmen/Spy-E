//
// Created by Deniz Sokmen on 17/03/15.
//

#include <SDL_image.h>
#include "graphics/Texture.h"
#include <stdio.h>

void Texture::createFromSDL(SDL_Surface *surface) {
    if (surface == NULL) {
        printf("Texture not found\n");
        return;
    }

    SDL_Surface *image = SDL_CreateRGBSurface(NULL, surface->w, surface->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(surface, NULL, image, NULL);


    id = 0;
	width = surface->w;
	height = surface->h;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    GLenum mode = GL_RGB;


    int numcols= surface->format->BytesPerPixel;
    if (numcols == 4)
    {
        if (surface->format->Rmask == 0x000000ff)
            mode = GL_RGBA;
        else
            mode = GL_BGRA;
    } else if (numcols == 3)     // no alpha channel
    {
        if (surface->format->Rmask == 0x000000ff)
            mode = GL_RGB;
        else
            mode = GL_BGR;
    } else {
        printf("warning: the image is not truecolor..  this will probably break\n");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void Texture::bind(GLuint unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);

}

void Texture::createFromSDL(SDL_Surface *surface, GLuint type) {
    this->type = type;

}
