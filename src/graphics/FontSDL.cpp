//
// Created by Deniz Sokmen on 17/03/15.
//

#include "graphics/FontSDL.h"
#include <SDL_ttf.h>
#include <GL/glew.h>
#include <wchar.h>
#include <graphics/Drawable.h>
#include "graphics/Drawer.h"
#include "graphics/Texture.h"

FontSDL::FontSDL(Drawer *drawer) {
	charSet.reserve(256);
	this->drawer = drawer;
}

FontSDL::~FontSDL() {

}

void FontSDL::loadFont(const char* fontname, int size) {
	TTF_Font* tmpfont;
	tmpfont = TTF_OpenFont(fontname, size);
	SDL_Color clr = { 0, 0, 255, 255 };

	for (unsigned short i = 1; i < 131; i++) {
		SDL_Surface *sText = TTF_RenderGlyph_Blended(tmpfont, i, clr);
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		//TODO: terminology. Using textures directly is wrong. 
		//should be encapsulated by another class named Glyph.
		Texture* texture = new Texture();
		texture->createFromSDL(sText);
		Drawable *drawable = new Drawable(texture);
		charSet[i] = drawable;
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
	offset.x +=12;
	while (txt[cnt] != '\0') {
		//TODO: textures should be drawn.
		//charSet[txt[cnt]]->draw(position + offset);
		position.x +=charSet[txt[cnt]]->getTexture()->width;
		//glm::vec3 newpos = position + offset;
		drawer->draw(charSet[txt[cnt]], glm::vec2(position.x, position.y));
		cnt++;
	}
}