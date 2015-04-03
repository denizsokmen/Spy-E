

#ifndef SPYE_LABEL_H
#define SPYE_LABEL_H

#include "graphics/ui/View.h"
#include "string"

class Label : public View {

private:
    std::wstring text;

public:
    void setText(std::wstring text);

    void draw();


};


#endif //SPYE_LABEL_H
