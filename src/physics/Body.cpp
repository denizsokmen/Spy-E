#include "physics/Body.h"

Body::Body(glm::vec3 *loc, glm::vec3 s, glm::vec3 acc, std::vector<glm::vec3> v){

    location = loc;
    speed = s;
    acceleration = acc;
    vertices = v;

    for(int i = 0; i < vertices.size(); i++){

        vertices[i].x += (*location).x;
        vertices[i].y += (*location).y;
        vertices[i].z += (*location).z;
    }

    boundingBox = new BoundingBox(vertices);
}

Body::~Body(){

}

void Body::setLocation(glm::vec3 loc) {
    *location = loc;
    boundingBox->update(loc);
}

void Body::setSpeed(glm::vec3 s) {
    speed = s;
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



