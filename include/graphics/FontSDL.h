#ifndef FONTSDL_H_INC
#define FONTSDL_H_INC
#include <vector>
#include <glm/glm.hpp>

class Texture;

class FontSDL {

public:
    FontSDL();
    ~FontSDL();
	
	std::vector<Texture*> charSet;
	void loadFont(const char *fontname, int size);
	void draw(glm::vec3 position, const wchar_t* text, ...);


};

#endif
