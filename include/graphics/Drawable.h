//
// Created by deniz on 21/03/15.
//

#ifndef _SPYE_DRAWABLE_H_
#define _SPYE_DRAWABLE_H_


class Texture;
class Drawable {
    Texture *texture;

public:
    Drawable(Texture *tex);

    Texture* getTexture();
};


#endif //_SPYE_DRAWABLE_H_
