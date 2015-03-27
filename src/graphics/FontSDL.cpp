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
	SDL_Color clr = { 255, 0, 255, 255 };
	SDL_Surface *sText;
	for (unsigned short i = 1; i < 131; i++) {
		sText = TTF_RenderGlyph_Blended(tmpfont, i, clr);
		//TODO: terminology. Using textures directly is wrong. 
		//should be encapsulated by another class named Glyph.
		Texture* texture = new Texture();
		texture->createFromSDL(sText);
		glyphs[i].code = i;
		TTF_GlyphMetrics(tmpfont, i, &glyphs[i].minx, &glyphs[i].maxx, &glyphs[i].miny, &glyphs[i].maxy, &glyphs[i].advance);
		Drawable *drawable = new Drawable(texture);
		glyphs[i].surface = drawable;
		delete sText;
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

	int sx = position.x;
	int sy = position.y;

	while (txt[cnt] != '\0') {
		int ch = (wchar_t)txt[cnt];
		if (ch == '\n') {
			position.y += 20;
			position.x = sx;

		}
		else {
			position.x += glyphs[ch].advance;
		}
		drawer->draw(glyphs[ch].surface, glm::vec2(position.x, position.y));
		//TODO: textures should be drawn.
		//charSet[txt[cnt]]->draw(position + offset);
		//position.x +=charSet[txt[cnt]]->getTexture()->width;
		//glm::vec3 newpos = position + offset;
		//drawer->draw(charSet[txt[cnt]], glm::vec2(position.x, position.y));
		cnt++;
	}
}