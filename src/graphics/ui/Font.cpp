#include <graphics/Drawable.h>
#include <graphics/Texture.h>
#include "graphics/ui/Font.h"

Font::Font(const char* fontName, int size){

    fontSDL->loadFont(fontName, size);
}

Font::~Font(){

}