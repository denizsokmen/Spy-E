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



void Menu::moveCursorUp() {
    if (this->cursor > 0 ) {
        Button *previousItem = this->getItem(this->cursor);
        unsigned int index = this->cursor - 1;
        Button *currentItem = this->getItem(index);
        this->reverseState(previousItem);
        this->reverseState(currentItem);
        this->setCursor(index);
    }
}

void Menu::moveCursorDown() {
    if (this->cursor < this->items.size() - 1) {
        Button *previousItem = this->getItem(this->cursor);
        unsigned int index = this->cursor + 1;
        Button *currentItem = this->getItem(index);
        this->reverseState(previousItem);
        this->reverseState(currentItem);
        this->setCursor(index);
    }
}

void Menu::setCursor(unsigned int index) {
    printf("[GUI][Menu] cursor is now: %i\n", index);
    this->cursor = index;
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
            Label *label = item->getLabel();


            int height = 16;
            Rect frame = Rect(this->frame.x, this->frame.y + (height+verticalSpace) * index++ , this->frame.w, this->frame.y);

            item->setFrame(frame);
            this->addSubview(item);

        }

        isSplitted= true;
    }
}


void Menu::setVerticalSpace(unsigned int space) {
    this->verticalSpace = space;
}


Menu::~Menu() {

}


void Menu::draw() {
    View::draw();
    this->placeButtons();

}

