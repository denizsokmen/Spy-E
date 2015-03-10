#include "physics/PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(){

}

PhysicsWorld::~PhysicsWorld() {

}

Body* PhysicsWorld::createBody(glm::vec3 loc, glm::vec3 speed, glm::vec3 acc){

    Body *body = new Body(loc, speed, acc);
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