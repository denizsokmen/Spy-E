#ifndef SPYE_FONT_H
#define SPYE_FONT_H

#include <graphics/FontSDL.h>

class Glyph;

class Font {



public:
    Glyph glyphs[256];
    std::vector<Drawable *> charSet;


    Font(const char* fontName, int size);
    ~Font();

};


#endif //SPYE_FONT_H
