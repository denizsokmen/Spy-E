//
// Created by Deniz Sokmen on 17/03/15.
//

#include "graphics/FontSDL.h"
#include <SDL_ttf.h>
#include <GL/glew.h>
#include "graphics/Texture.h"

FontSDL::FontSDL() {
	charSet.reserve(256);
}

FontSDL::~FontSDL() {

}

void FontSDL::loadFont(const char* fontname, int size) {
	TTF_Font* tmpfont;
	tmpfont = TTF_OpenFont(fontname, size);
	SDL_Color clr = { 0, 0, 255, 0 };

	for (unsigned short i = 65; i < 91; i++) {
		SDL_Surface *sText = TTF_RenderGlyph_Blended(tmpfont, i, clr);

		//TODO: terminology. Using textures directly is wrong. 
		//should be encapsulated by another class named Glyph.
		Texture* texture = new Texture();
		texture->createFromSDL(sText);
		charSet[i] = texture;
		SDL_FreeSurface(sText);
	}
	
	TTF_CloseFont(tmpfont);
}

void FontSDL::draw(glm::vec3 position, const wchar_t* text, ...) {
	wchar_t txt[256];
	va_list ap;
	va_start(ap, text);
	vswprintf(txt, 255, text, ap);
	va_end(ap);

	int cnt = 0;
	glm::vec3 offset(0.0f, 0.0f, 0.0f);
	while (txt[cnt] != '\0') {

		//TODO: textures should be drawn.
		//offset.x += charSet[txt[cnt]]->width; ??
		//charSet[txt[cnt]]->draw(position + offset);
		cnt++;
	}
}