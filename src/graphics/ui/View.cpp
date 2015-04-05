//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/View.h"


void View::addSubview(View *view) {
    view->setSystem(this->system);
    this->subViews.push_back(view);
    printf("[GUI] Added a subview count: %i\n", this->subViews.size());
}

void View::draw() {
    for (auto subView : subViews) {
        subView->draw();
    }
}

void View::setSystem(GUI *system) {
    this->system = system;
}

GUI *View::getSystem() {
    return this->system;
}

void View::setFrame(Rect frame) {
    this->frame = frame;
}
