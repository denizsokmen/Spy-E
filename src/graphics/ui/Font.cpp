#include <graphics/Drawable.h>
#include <graphics/Texture.h>
#include "graphics/ui/Font.h"
#include <SDL_ttf.h>


Font::Font(const char* fontName, int size){
    charSet.reserve(256);

    TTF_Font *tmpfont;
    tmpfont = TTF_OpenFont(fontName, size);
    SDL_Color clr = {255, 255, 255, 255};
    SDL_Color clr2 = {0, 0, 255, 255};
    TTF_SetFontStyle(tmpfont, TTF_STYLE_NORMAL);
    TTF_SetFontHinting(tmpfont, TTF_HINTING_NONE);
    SDL_Surface *sText;
    for (unsigned short i = 1; i < 131; i++) {
        sText = TTF_RenderGlyph_Blended(tmpfont, i, clr);
        //TODO: terminology. Using textures directly is wrong.
        //should be encapsulated by another class named Glyph.
        Texture *texture = new Texture();
        texture->createFromSDL(sText);
        glyphs[i].code = i;
        TTF_GlyphMetrics(tmpfont, i, &glyphs[i].minx, &glyphs[i].maxx, &glyphs[i].miny, &glyphs[i].maxy,
                         &glyphs[i].advance);
        printf("%d, %d, %d, %d, %d, %d, %d, %c\n", glyphs[i].minx, glyphs[i].maxx, glyphs[i].miny, glyphs[i].maxy,
               glyphs[i].advance, texture->width, texture->height, i);
        Drawable *drawable = new Drawable(texture);
        glyphs[i].surface = drawable;
        glm::vec2 offset = glm::vec2(texture->width / 2 + glyphs[i].minx, 0);
        glyphs[i].offset = offset;
        // delete sText;
    }

    TTF_CloseFont(tmpfont);

}

Font::~Font(){

}