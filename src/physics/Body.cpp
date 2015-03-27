#include "physics/Body.h"

Body::Body(glm::vec3 *loc, glm::vec3 s, glm::vec3 acc, std::vector<glm::vec3> v){

    location = loc;
    speed = s;
    acceleration = acc;
    vertices = v;

    for(int i = 0; i < vertices.size(); i++){

        vertices[i].x = vertices[i].x+(*location).x;
        vertices[i].y = vertices[i].z+(*location).y;
        vertices[i].z = vertices[i].z+(*location).z;
    }

    boundingBox = new BoundingBox(vertices);
}

Body::~Body(){

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

void Body::updateBoundingBox(std::vector<glm::vec3> v){

    vertices = v;

    for(int i = 0; i < vertices.size(); i++){

        vertices[i].x = vertices[i].x+(*location).x;
        vertices[i].y = vertices[i].z+(*location).y;
        vertices[i].z = vertices[i].z+(*location).z;
    }
    delete boundingBox;
    boundingBox = new BoundingBox(vertices);
}