#include "physics/Body.h"

Body::Body(glm::vec3 loc, glm::vec3 s, glm::vec3 acc){

    location = loc;
    speed = s;
    acceleration = acc;
}

Body::~Body(){

}

void Body::setLocation(glm::vec3 loc) {

    location = loc;
}

void Body::setSpeed(glm::vec3 s) {

    speed = s;
}

glm::vec3 Body::getAcceleration() {

    return acceleration;
}

glm::vec3 Body::getSpeed() {

    return speed;
}

glm::vec3 Body::getLocation(){

    return location;
}