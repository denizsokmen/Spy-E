#ifndef TEXTURE_H_INC
#define TEXTURE_H_INC

#include <SDL_surface.h>
#include <GL/glew.h>

class Texture {

public:

    void createFromSDL(SDL_Surface* surface);

	int width;
	int height;
    GLuint id;
};


#endif