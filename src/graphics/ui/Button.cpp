//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/Button.h"
#include "graphics/ui/Image.h"
#include "graphics/ui/Label.h"

Button::Button() : View() {
    this->state = ControlState::Normal;
    this->styleMap[ControlState::Normal] = new Style();
    this->styleMap[ControlState::Selected] = new Style();
    this->backgroundImage = new Image();
    this->titleLabel = new Label();
}

void Button::setTarget(std::function<void()> target) {
    this->target = target;
}

void Button::runTarget() {
    this->target();
}

void Button::setText(std::wstring text, ControlState state) {
    Style *style = styleMap[state];
    style->text = text;

}

void Button::setImage(Texture *image, ControlState state) {
    Style *style = styleMap[state];
    style->image = image;
}

void Button::setFrame(Rect frame) {
    View::setFrame(frame);
    this->backgroundImage->setFrame(frame);
    this->titleLabel->setFrame(frame);
}

void Button::draw() {
    View::draw();
}


Button::~Button() {
    for (std::map<ControlState, Style *>::iterator iterator = styleMap.begin();
         iterator != styleMap.end();
         ++iterator) {

        Style *style = iterator->second;
        delete style;
    }

}
