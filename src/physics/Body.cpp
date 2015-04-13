#include "physics/Body.h"

Body::Body(Entity* bodyEntity, std::vector<glm::vec3> v){

    this -> entity = bodyEntity;
    this -> location = &bodyEntity->position;
    this -> speed = zeroVector;
    this -> acceleration = zeroVector;
    this -> vertices = v;
    boundingBox = new BoundingBox(vertices);
}

void Body::setLocation(glm::vec3 loc) {
    *location = loc;
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

    return *location;
}

BoundingBox* Body::getBoundingBox(){

    return boundingBox;
}

std::vector<glm::vec3> Body::getVertices() {
    return this->vertices;
}


void Body::setAcceleration(glm::vec3 acceleration) {
    this->acceleration = acceleration;
}

void Body::setAcceleration(float acceleration, char direction) {
    switch (direction) {
        case 'x':
            this->acceleration.x = acceleration;
            break;
        case 'y':
            this->acceleration.y = acceleration;
            break;
        case 'z':
            this->acceleration.z = acceleration;
            break;
        default:
            printf("No such direction!");
            break;
    }
}

void Body::setSpeed(float speed, char direction){
    switch (direction) {
        case 'x':
            this->speed.x = speed;
            break;
        case 'y':
            this->speed.y = speed;
            break;
        case 'z':
            this->speed.z = speed;
            break;
        default:
            printf("No such direction!");
            break;
    }
}

void Body::setLocation(float location, char direction) {
    switch (direction) {
        case 'x':
            (*this->location).x = location;
            break;
        case 'y':
            (*this->location).y = location;
            break;
        case 'z':
            (*this->location).z = location;
            break;
        default:
            printf("No such direction!");
            break;
    }
}

Body::~Body(){

}

void Body::addAcceleration(float acceleration, char direction) {
    switch (direction) {
        case 'x':
            this->acceleration.x += acceleration;
            break;
        case 'y':
            this->acceleration.y += acceleration;
            break;
        case 'z':
            this->acceleration.z += acceleration;
            break;
        default:
            printf("No such direction!");
            break;
    }
}

Entity *Body::getEntity() {
    return this->entity;
}

BoundingBox *Body::getBoundingBoxFromLocation() {

    std::vector<glm::vec3> tempVertices1 = this->vertices;

    for(int i = 0; i < tempVertices1.size(); i++){
        tempVertices1[i].x += this->getLocation().x;
        tempVertices1[i].y += this->getLocation().y;
        tempVertices1[i].z += this->getLocation().z;
    }

    return new BoundingBox(tempVertices1);
}
