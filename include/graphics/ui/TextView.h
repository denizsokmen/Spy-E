//
// Created by Enes Şenel on 03/04/15.
//

#ifndef SPYE_TEXTVIEW_H
#define SPYE_TEXTVIEW_H

#include <string>
#include "graphics/ui/View.h"
#include "graphics/ui/Font.h"

class TextView: public View {

private:
    int numberOfLines;
    bool isTextSplitted;
    Font* font;
    std::wstring text;

public:
    TextView();
    ~TextView();
    void setFont(Font* font);

    void setText(std::wstring text);

    void createNewLabel(std::wstring text);

    void draw();

    void splitText();
};


#endif //SPYE_TEXTVIEW_H
