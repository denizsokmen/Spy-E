#include "physics/Face.h"

Face::Face(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint) {
    this->firstPoint = firstPoint;
    this->secondPoint = secondPoint;
    this->thirdPoint = thirdPoint;
}

bool Face::intersects(glm::vec3 direction, glm::vec3 origin) {
    return false;
}


Face::~Face() {

}

