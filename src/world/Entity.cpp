

#include "world/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Entity::Entity() {
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::quat Entity::getOrientation() const {
    return orientation;
}

void Entity::setOrientation(glm::quat &orientation) {
    this->orientation = orientation;
}

glm::vec3 Entity::getPosition() const {
    return position;
}

void Entity::setPosition(glm::vec3 &position) {
    this->position = position;
}