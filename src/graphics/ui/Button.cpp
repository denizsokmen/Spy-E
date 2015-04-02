//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/Button.h"

Button::Button() {

}

void Button::setTarget(std::function<void()> target) {
    this->target = target;
}

void Button::runTarget() {
    this->target();
}
