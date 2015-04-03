#ifndef SPYE_FONT_H
#define SPYE_FONT_H

#include <graphics/FontSDL.h>

class Font {

public:
    Font(const char* fontName, int size);
    ~Font();

    FontSDL* fontSDL;
};


#endif //SPYE_FONT_H
