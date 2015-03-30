#include "physics/PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(){
    bounce = false;
}

PhysicsWorld::~PhysicsWorld() {

}

Body* PhysicsWorld::createBody(glm::vec3 *loc, glm::vec3 speed, glm::vec3 acc, std::vector<glm::vec3> v){

    Body *body = new Body(loc, speed, acc, v);
    bodies.push_back(body);

    return body;
}

void PhysicsWorld::update(float dt) {

    for (Body *body : bodies) {
        if(body->getSpeed() != glm::vec3(0,0,0) || body->getAcceleration() != glm::vec3(0,0,0)) {

            applyAirFriction(body);

            glm::vec3 acceleration = body->getAcceleration();
            glm::vec3 speed = body->getSpeed();
            glm::vec3 location = body->getLocation();

            glm::vec3 updatedSpeed = getUpdatedSpeed(dt, acceleration, speed);
            body->setSpeed(updatedSpeed);

            glm::vec3 updatedLocation = getUpdatedLocation(dt, acceleration, location, updatedSpeed);
            body->setLocation(updatedLocation);

            for (Body *controlBody : bodies) {
                if (body != controlBody) {
                    if (isCollided(body, controlBody)) {
                        body->setLocation(location);
                        if (body->getLocation().y <= 2.5f) {
                            body->setLocation(2.01f, 'y');
                            if(bounce)
                                body->setSpeed(-(body->getSpeed().y), 'y'); //for bouncing floor
                            else
                                body->setSpeed(0, 'y'); //for non-bouncing floor

                        }/*
                        else {
                            body->setSpeed(-(body->getSpeed().x), 'x');
                            body->setSpeed(-(body->getSpeed().z), 'z');
                        }*/

                    }
                }
            }
        }
    }
}

void PhysicsWorld::applyAirFriction(Body *body) {
    if(body->getSpeed().x != 0)
                body->setAcceleration(-(body->getSpeed().x), 'x');
    if(body->getSpeed().z != 0)
                body->setAcceleration(-(body->getSpeed().z), 'z');
}

glm::vec3 PhysicsWorld::getUpdatedLocation(float dt, glm::vec3 &acceleration, glm::vec3 &location,
                                           glm::vec3 &updatedSpeed) {//X = Xo + Vo.t + 1/2*a*t^2
    float updatedLocationX = location.x + (updatedSpeed.x * dt) + (0.5f * acceleration.x * dt * dt);
    float updatedLocationY = location.y + (updatedSpeed.y * dt) + (0.5f * acceleration.y * dt * dt);
    float updatedLocationZ = location.z + (updatedSpeed.z * dt) + (0.5f * acceleration.z * dt * dt);
    glm::vec3 updatedLocation = glm::vec3(updatedLocationX, updatedLocationY, updatedLocationZ);
    return updatedLocation;
}

glm::vec3 PhysicsWorld::getUpdatedSpeed(float dt, glm::vec3 &acceleration, glm::vec3 &speed) {
    float updatedSpeedX = speed.x + acceleration.x * dt;
    float updatedSpeedY = speed.y + acceleration.y * dt;
    float updatedSpeedZ = speed.z + acceleration.z * dt;
    glm::vec3 updatedSpeed = glm::vec3(updatedSpeedX, updatedSpeedY, updatedSpeedZ);
    return updatedSpeed;
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

bool PhysicsWorld::isCollidedX(Body *b1, Body *b2) {

    BoundingBox *box1 = b1->getBoundingBox();
    BoundingBox *box2 = b2->getBoundingBox();

    return ( box1->getMaxVertex().x > box2->getMinVertex().x &&
             box1->getMinVertex().x < box2->getMaxVertex().x);

}

bool PhysicsWorld::isCollidedY(Body *b1, Body *b2) {

    BoundingBox *box1 = b1->getBoundingBox();
    BoundingBox *box2 = b2->getBoundingBox();

    return ( box1->getMaxVertex().y > box2->getMinVertex().y &&
             box1->getMinVertex().y < box2->getMaxVertex().y);

}

bool PhysicsWorld::isCollidedZ(Body *b1, Body *b2) {

    BoundingBox *box1 = b1->getBoundingBox();
    BoundingBox *box2 = b2->getBoundingBox();

    return ( box1->getMaxVertex().z > box2->getMinVertex().z &&
             box1->getMinVertex().z < box2->getMaxVertex().z );

}
