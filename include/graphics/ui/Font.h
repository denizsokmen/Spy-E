#ifndef SPYE_FONT_H
#define SPYE_FONT_H

#include <vector>
#include <glm/glm.hpp>

class Drawable;

class Glyph {

public:
    int code;
    int minx, maxx;
    int miny, maxy;
    int advance;
    Drawable *surface;
    int usecount;
    glm::vec2 offset;
};


class Font {

public:
    Glyph glyphs[256];
    std::vector<Drawable *> charSet;

    int getHeight();
    Font(const char* fontName, int size);
    ~Font();

};


#endif //SPYE_FONT_H
