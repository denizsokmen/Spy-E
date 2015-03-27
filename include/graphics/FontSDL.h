#ifndef FONTSDL_H_INC
#define FONTSDL_H_INC
#include <vector>
#include <glm/glm.hpp>

class Texture;
class Drawer;
class Drawable;


class Glyph {

public:
	int code;
	int minx, maxx;
	int miny, maxy;
	int advance;
	Drawable* surface;
	int usecount;
	glm::vec2 offset;
};

class FontSDL {
	Drawer* drawer;
public:
    FontSDL(Drawer* drawer);
    ~FontSDL();
	
	std::vector<Drawable*> charSet;
	Glyph glyphs[256];
	void loadFont(const char *fontname, int size);
	void draw(glm::vec3 position, const wchar_t* text, ...);


};

#endif
