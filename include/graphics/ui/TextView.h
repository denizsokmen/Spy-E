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
    Font* font;

public:
    TextView(Font* font);
    ~TextView();
    void setFont(Font* font);
    void setText(std::string text);
    void createNewLabel(std::string text);
};


#endif //SPYE_TEXTVIEW_H
