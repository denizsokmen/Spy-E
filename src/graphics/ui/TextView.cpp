#include <graphics/Drawable.h>
#include <graphics/Texture.h>
#include "graphics/ui/TextView.h"

TextView::TextView(Font* font){
    this->font = font;
    setFont(font);
}

void TextView::setFont(Font* font){
    this->font = font;
}

void TextView::setText(std::string text){
    float textWidth;
    int start = 0;
    int end = 0;

    for(auto ch: text) {
        textWidth += this->font->glyphs[ch].surface->texture->width;
        end++;
        if(textWidth == this->frame.w){
            createNewLabel(text.substr(start, end));
            start = end + 1;
        }
    }
}

void TextView::createNewLabel(std::string text) {

}
