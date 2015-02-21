//
//  Renderable.cpp
//  Spy-E
//
//  Created by Taha Doğan Güneş on 21/02/15.
//  Copyright (c) 2015 Spy-E. All rights reserved.
//

#include "Renderable.h"

glm::vec3 Renderable::getPosition() {
    return this->position;
}

void Renderable::setPosition(glm::vec3 position) {
    this->position = position;
}
