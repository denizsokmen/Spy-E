//
// Created by Taha Doğan Güneş on 02/04/15.
//

#include "graphics/ui/View.h"


void View::addSubview(View *view) {
    this->subViews.push_back(view);
}
