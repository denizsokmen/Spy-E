//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/Label.h"
#include "graphics/ui/Font.h"
#include "graphics/ui/GUI.h"
#include "graphics/Drawer.h"
#include "graphics/Drawable.h"
#include "graphics/Texture.h"
#include <glm/glm.hpp>


Label::Label() : View() {
    this->setText(L"");
    this->font = NULL;
}


Label::Label(std::wstring text) : View() {
    this->setText(text);
    this->font = NULL;
}

void Label::setText(std::wstring text) {
    this->text = text;
}

void Label::setText(const wchar_t *text, ...) {
    wchar_t txt[256];
    va_list ap;
    va_start(ap, text);
    vswprintf(txt, 255, text, ap);
    va_end(ap);
    this->text = txt;
}

void Label::setFont(const char *name, int size) {
    this->font = new Font(name, size);
}

void Label::setFont(Font *font) {
    this->font = font;
}

void Label::draw() {
    View::draw();

    if (this->font == NULL) {
        GUI* gui = this->getSystem();
        this->font = gui->font;
    }


    wchar_t *tempText = (wchar_t *) this->text.c_str();

//    printf("Label in: x:%f y:%f text:%s\n", this->frame.x, this->frame.y, this->text.c_str());
    glm::vec3 position = glm::vec3(this->frame.x, this->frame.y, 0);

    int cnt = 0;
    glm::vec3 offset(0.0f, 0.0f, 0.0f);
    offset.x += 12;

    int sx = position.x;
    int sy = position.y;

    while (tempText[cnt] != '\0') {
        int ch = (wchar_t) tempText[cnt];


        //TODO: textures should be drawn.
        //charSet[txt[cnt]]->draw(position + offset);
        //position.x +=charSet[txt[cnt]]->getTexture()->width;
        //glm::vec3 newpos = position + offset;
        //drawer->draw(charSet[txt[cnt]], glm::vec2(position.x, position.y));

        if (ch == '\n') {
            position.y += 20;
            position.x = sx;

        }
        else {
            this->getSystem()->drawer->draw(this->font->glyphs[ch].surface,
                                            glm::vec2(position.x, position.y),
                                            glm::vec2(this->font->glyphs[ch].surface->getTexture()->width,
                                                      this->font->glyphs[ch].surface->getTexture()->height));
            position.x += this->font->glyphs[ch].advance;
        }
        cnt++;

    }


}

Font *Label::getFont() {
    return this->getFont();
}
