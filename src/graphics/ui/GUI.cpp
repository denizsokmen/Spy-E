#include "graphics/ui/GUI.h"
#include "graphics/ui/View.h"
#include "graphics/ui/Font.h"

GUI::GUI(Drawer* drawer) {
    this->mainView = new View();
    this->mainView->setSystem(this);
    this->drawer = drawer;
    this->font = new Font("fonts/Arial.ttf", 16);
}

GUI::GUI(Drawer* drawer, Input* input) {
    this->mainView = new View();
    this->mainView->setSystem(this);
    this->drawer = drawer;
    this->font = new Font("fonts/Arial.ttf", 16);
    this->input = input;
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
    view->setSystem(this);
    this->mainView->addSubview(view);
}

void GUI::addSubview(View *view, std::string tag) {
    view->setSystem(this);
    view->setTag(tag);
    this->mainView->addSubview(view);
}

GUI::~GUI() {
    delete this->font;
}

View *GUI::viewWithTag(std::string tag) {
    return this->mainView->viewWithTag(tag);
}

Input *GUI::getInput() {
    return this->input;
}
