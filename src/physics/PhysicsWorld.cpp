#include "physics/PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(){

}

PhysicsWorld::~PhysicsWorld() {

}

Body* PhysicsWorld::createBody(glm::vec3 loc, glm::vec3 speed, glm::vec3 acc, std::vector<glm::vec3> v){

    Body *body = new Body(loc, speed, acc, v);
    bodies.push_back(body);

    return body;
}

void PhysicsWorld::update(float dt) {

    for (Body *body : bodies) {
        
        glm::vec3 acceleration = body->getAcceleration();
        glm::vec3 speed = body->getSpeed();
        glm::vec3 location = body->getLocation();

        //X = Xo + Vo.t + 1/2*a*t^2
        float updatedLocationX = location.x + (speed.x * dt) + (0.5f * acceleration.x * dt * dt);
        float updatedLocationY = location.y + (speed.y * dt) + (0.5f * acceleration.y * dt * dt);
        float updatedLocationZ = location.z + (speed.z * dt) + (0.5f * acceleration.z * dt * dt);

        //V = Vo + a*t
        float updatedSpeedX = speed.x + acceleration.x * dt;
        float updatedSpeedY = speed.y + acceleration.y * dt;
        float updatedSpeedZ = speed.z + acceleration.z * dt;


        body->setSpeed(glm::vec3(updatedSpeedX, updatedSpeedY, updatedSpeedZ));
        body->setLocation(glm::vec3(updatedLocationX, updatedLocationY, updatedLocationZ));
    }
}

bool PhysicsWorld::isCollided(Body *b1, Body *b2){

    BoundingBox *box1 = b1->getBoundingBox();
    BoundingBox *box2 = b2->getBoundingBox();

    return ( box1->getMaxVertex().x > box2->getMinVertex().x &&
             box1->getMinVertex().x < box2->getMaxVertex().x &&
             box1->getMaxVertex().y > box2->getMinVertex().y &&
             box1->getMinVertex().y < box2->getMaxVertex().y &&
             box1->getMaxVertex().z > box2->getMinVertex().z &&
             box1->getMinVertex().z < box2->getMaxVertex().z   );

}