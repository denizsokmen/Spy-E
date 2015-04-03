//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/GUI.h"
#include "graphics/ui/View.h"

GUI::GUI(Drawer *drawer) {
    this->mainView = new View();
    this->mainView->setSystem(this);
    this->drawer = drawer;
}


void GUI::init() {


}

void GUI::update(float dt) {

}

void GUI::draw() {

}

void GUI::draw2D() {

    this->mainView->draw();
}

void GUI::addSubview(View *view) {

    this->mainView->addSubview(view);

}


