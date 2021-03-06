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
    this->backgroundImage = new Image("./assets/texture/debug/rectangle.png");
    this->titleLabel = new Label();
    this->addSubview(backgroundImage);
    this->addSubview(titleLabel);
    this->setTarget([this](){
        printf ("[GUI][Button] Target of '%s' button is empty!.\n", this->getTag().c_str());
    });
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
    this->setState(state);
}

void Button::setImage(Texture *texture, ControlState state) {
    Style *style = styleMap[state];
    style->texture = texture;
    this->setState(state);
}

void Button::setFrame(Rect frame) {
    View::setFrame(frame);
    this->backgroundImage->setFrame(frame);
    this->titleLabel->setFrame(frame);
}

void Button::draw() {
    View::draw();
}


void Button::setState(ControlState state) {
    this->state = state;
    Style *style = this->styleMap[state];
    Texture *texture = style->texture;
    std::wstring text = style->text;


    this->backgroundImage->setTexture(texture);

    this->titleLabel->setText(text);
}

Button::~Button() {
    for (std::map<ControlState, Style *>::iterator iterator = styleMap.begin();
         iterator != styleMap.end();
         ++iterator) {

        Style *style = iterator->second;
        delete style;
    }
}

ControlState Button::getState() {
    return this->state;
}

Label *Button::getLabel() {
    return this->titleLabel;
}


void Button::setText(std::string text, ControlState state) {
    std::wstring wstring;
    wstring.assign(text.begin(), text.end());
    this->setText(wstring, state);
}

void Button::setText(std::string text) {
    std::wstring wstring;
    wstring.assign(text.begin(), text.end());
    this->setText(wstring);
}

void Button::setText(std::wstring text) {
    this->setText(text, Normal);
    this->setText(text, Selected);
}

bool Button::isMouseInside() {
    bool isInside = View::isMouseInside();
    if(isInside)
        this->runTarget();
    return isInside;

}

