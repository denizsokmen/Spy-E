
#ifndef SPYE_BUTTON_H
#define SPYE_BUTTON_H

#include <graphics/ui/View.h>
#include <functional>
#include <string>
#include <map>

class Texture;

class Image;

class Label;

enum ControlState {
    Normal,
    Selected
};

class Style {
public:
    Color color;
    Texture *image;
    std::wstring text;

    Style() {
        color = Color();
        image = NULL;
    }

};


class Button : public View {

protected:
    void runTarget();

private:
    Image *backgroundImage;
    Label *titleLabel;

    ControlState state;
    std::map<ControlState, Style *> styleMap;
    std::function<void()> target;

public:
    Button();

    void setText(std::wstring text, ControlState state);

    void setImage(Texture *image, ControlState state);
    void setTarget(std::function<void()> target);

    ~Button();

    void setFrame(Rect frame);

    void draw();
};


#endif //SPYE_BUTTON_H
