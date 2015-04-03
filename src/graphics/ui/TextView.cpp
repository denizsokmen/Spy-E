#include <graphics/Drawable.h>
#include <graphics/Texture.h>
#include "graphics/ui/TextView.h"
#include "graphics/ui/Label.h"
#include "graphics/ui/GUI.h"

TextView::TextView() {
    isTextSplitted = false;
}

void TextView::setFont(Font* font){
    this->font = font;
}

void TextView::setText(std::wstring text) {
    this->text = text;
    isTextSplitted = false;
}

void TextView::createNewLabel(std::wstring text) {
    Label *newLabel = new Label(text);
    float height = this->font->glyphs[12].surface->texture->height * numberOfLines;
    numberOfLines++;
    newLabel->frame = Rect(this->frame.x, this->frame.y + height, this->frame.w, this->frame.h);
    this->addSubview(newLabel);
}


void TextView::draw() {
    View::draw();

    if (!isTextSplitted && this->text != L"") {
        printf("[GUI][TextView] isTextSplitted is false\n");
        splitText();
        isTextSplitted = true;
    }
}

void TextView::splitText() {
    this->setFont(getSystem()->font);

    float textWidth = 0.0f;
    int startingPoint = 0;
    int lineLength = 0;
    numberOfLines = 0;

    for (auto ch: this->text) {
        textWidth += font->glyphs[ch].surface->texture->width;
        printf("[GUI][TextView] textWidth is %f\n", textWidth);
        lineLength++;
        if (textWidth >= this->frame.w) {
            std::wstring s = text.substr(startingPoint, lineLength);
            printf("[GUI][TextView] splitted value: %s \n", s.c_str());
            createNewLabel(s);
            startingPoint = lineLength + 1;
            lineLength = 0;
            textWidth = 0;
        }
    }
}
