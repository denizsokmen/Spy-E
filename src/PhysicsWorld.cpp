#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(){

}

PhysicsWorld::~PhysicsWorld() {

}

Body PhysicsWorld::createBody(glm::vec3 loc, glm::vec3 speed, glm::vec3 acc){

    Body *body = new Body(loc, speed, acc);
    bodies.push_back(body);

    return body;
}