
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
    Texture *texture;
    std::wstring text;

    Style() {
        color = Color();
        texture = NULL;
    }
};

class Button : public View {
private:
    Image *backgroundImage;
    Label *titleLabel;

    ControlState state;
    std::map<ControlState, Style *> styleMap;
    std::function<void()> target;

public:
    Button();
    ~Button();

    void setText(std::wstring text, ControlState state);
    void setText(std::string text, ControlState state);
    void setText(std::string text);
    void setText(std::wstring text);

    void setFrame(Rect frame);
    void setState(ControlState state);
    void setImage(Texture *image, ControlState state);
    void setTarget(std::function<void()> target);
    void runTarget();

    ControlState getState();
    Label *getLabel();

    // View's virtual functions
    void draw();
    bool isMouseInside();
};


#endif //SPYE_BUTTON_H
