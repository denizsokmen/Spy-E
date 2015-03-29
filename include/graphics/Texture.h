#ifndef TEXTURE_H_INC
#define TEXTURE_H_INC

#include <SDL_surface.h>
#include <GL/glew.h>

class Texture {

public:

    void createFromSDL(SDL_Surface* surface);
	void bind(GLuint unit);

	int width;
	int height;

    GLuint getId() const {
        return id;
    }

    GLuint id;
};


#endif