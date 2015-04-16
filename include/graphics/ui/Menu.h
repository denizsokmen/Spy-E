//
// Created by Taha Doğan Güneş on 05/04/15.
//

#ifndef SPYE_MENU_H
#define SPYE_MENU_H

#include <vector>
#include "graphics/ui/View.h"

class Button;


class Menu : public View {

private:
    std::vector<Button *> items;
    unsigned int cursor;
    bool isSplitted;
    unsigned verticalSpace;
    void placeButtons();


public:
    Menu();
    ~Menu();



    Button *getItem(unsigned int index);

    void runSelected();
    void addItem(Button *item);
    void setCursor(unsigned int index);
    void reverseState(Button *item);
    void clear();
    void draw();
    void moveCursorUp();
    void moveCursorDown();

    void reverseState(unsigned int index);

    Button *getSelectedItem();


};


#endif //SPYE_MENU_H
