//
// Created by Taha Doğan Güneş on 05/04/15.
//

#include "graphics/ui/Button.h"
#include "graphics/ui/Label.h"
#include "graphics/ui/Menu.h"
#include "graphics/ui/Font.h"

Menu::Menu() : View() {
    this->cursor = 0;
    this->verticalSpace = 0;
    isSplitted = false;

}



void Menu::addItem(Button *item) {

    if (this->items.size() == 0)
        item->setState(Selected);
    else
        item->setState(Normal);
    this->items.push_back(item);
}


Button *Menu::getItem(unsigned int index) {
    return this->items.at(index);
}

Button *Menu::getSelectedItem() {
    return this->items.at(this->cursor);
}


void Menu::moveCursorUp() {
    if (this->cursor > 0 ) {
        this->reverseState(this->cursor);
        this->reverseState(this->cursor-1);
        this->setCursor(this->cursor-1);
    }
}

void Menu::moveCursorDown() {
    if (this->cursor < this->items.size() - 1) {
        this->reverseState(this->cursor);
        this->reverseState(this->cursor+1);
        this->setCursor(this->cursor+1);
    }
}

void Menu::setCursor(unsigned int index) {
    printf("[GUI][Menu] cursor is now: %i\n", index);
    this->cursor = index;
}

void Menu::reverseState(unsigned int index) {
    Button* item = this->getItem(index);
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

void Menu::placeButtons() {
    if (!isSplitted) {
        printf("[GUI][Menu] isSplitted is false\n");
        unsigned int index = 0;
        for (auto item: items) {
            //FIXME: Height must be calculated from label's font
            //Label *label = item->getLabel();
            int height = 16;
            Rect frame = Rect(this->frame.x,
                              this->frame.y + (height+verticalSpace) * index++,
                              this->frame.w,
                              this->frame.h / items.size());
            item->setFrame(frame);
            this->addSubview(item);
        }

        isSplitted= true;
    }
}


void Menu::setVerticalSpace(unsigned int space) {
    this->verticalSpace = space;
}

void Menu::draw() {
    View::draw();
    this->placeButtons();

}

void Menu::runSelected() {
    this->getSelectedItem()->runTarget();
}

Menu::~Menu() {

}



