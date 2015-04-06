//
// Created by Taha Doğan Güneş on 05/04/15.
//

#include "graphics/ui/Button.h"
#include "graphics/ui/Label.h"
#include "graphics/ui/Menu.h"
#include "graphics/ui/Font.h"

Menu::Menu() : View() {
    this->cursor = 0;
}

void Menu::addItem(Button *item) {
    this->items.push_back(item);
    Label *label = item->getLabel();
    Font *font = label->getFont();
    int height = font->getHeight();
    Rect frame = Rect(this->frame.x, this->frame.y + height * this->items.size(), this->frame.w, this->frame.y);
    item->setFrame(frame);
    this->addSubview(item);
}


Button *Menu::getItem(unsigned int index) {
    return this->items.at(index);
}

void Menu::setCursor(unsigned int index) {
    Button *item = this->getItem(index);
    this->cursor = index;
    this->reverseState(item);
}

void Menu::reverseState(Button *item) {
    ControlState state = item->getState();
    switch (state) {
        case ControlState::Normal:
            item->setState(ControlState::Selected);
            break;

        case ControlState::Selected:
            item->setState(ControlState::Normal);
            break;
    }
}


void Menu::clear() {
    this->items.clear();
}

Menu::~Menu() {

}



