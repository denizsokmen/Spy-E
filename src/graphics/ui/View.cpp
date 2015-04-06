//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/View.h"

View::View() {

}

void View::addSubview(View *view) {

    this->subViews.push_back(view);
    this->setSystem(this->system);
    printf("[GUI] Added a subview count: %i\n", this->subViews.size());
}

void View::draw() {
    for (auto subView : subViews) {
        subView->draw();
    }
}

void View::setSystem(GUI *system) {
    this->system = system;
    for (auto subView : subViews) {
        subView->setSystem(system);
    }
}

GUI *View::getSystem() {
    return this->system;
}

void View::setFrame(Rect frame) {
    this->frame = frame;
}


View::~View() {
    for (auto subView : subViews) {
        delete subView;
    }
}
