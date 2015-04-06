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
    void placeButtons();

public:
    Menu();

    ~Menu();

    void addItem(Button *item);

    Button *getItem(unsigned int index);

    void setState(unsigned int index);
    void setCursor(unsigned int index);

    void reverseState(Button *item);

    void clear();
    void draw();





};


#endif //SPYE_MENU_H
