

#ifndef SPYE_LABEL_H
#define SPYE_LABEL_H

#include "graphics/ui/View.h"
#include "string"

class Font;

class Label : public View {

private:


    std::wstring text;
    Font *font;

public:
    Label();
    Label(const wchar_t *text, ...);
    Label(std::wstring text);

    void setText(std::wstring text);

    void setFont(const char *name, int size);
    void setFont(Font *font);

    Font *getFont();

    void draw();


    void setText(wchar_t const *text, ...);
    void setText(const wchar_t *text, va_list args);

};


#endif //SPYE_LABEL_H
