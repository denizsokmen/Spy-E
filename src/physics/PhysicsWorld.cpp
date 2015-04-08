#include "physics/PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(){
    bounce = false;
}

PhysicsWorld::~PhysicsWorld() {

}

Body* PhysicsWorld::createBody(Entity* bodyEntity, std::vector<glm::vec3> vertices){

    Body *body = new Body(bodyEntity, vertices);
    bodies.push_back(body);
    return body;
}

void PhysicsWorld::update(float dt) {

    for (Body *body : bodies) {
        if(body->getSpeed() != zeroVector || body->getAcceleration() != zeroVector) {

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
                            body->setLocation(2.001f, 'y');
                            if(bounce)
                                body->setSpeed(-(body->getSpeed().y), 'y');
                            else
                                body->setSpeed(0, 'y');
                        } else {
                            printf("a");
                            body->setAcceleration(0, 'z');
                            body->setAcceleration(0, 'x');
                        }
                    }
                }
            }
        }
    }
}

void PhysicsWorld::applyAirFriction(Body *body) {
    //doesn't work
    body->addAcceleration(-(body->getSpeed().x)/2, 'x');
    body->addAcceleration(-(body->getSpeed().z)/2, 'z');
}

glm::vec3 PhysicsWorld::getUpdatedLocation(float dt, glm::vec3 &acceleration, glm::vec3 &location,
                                           glm::vec3 &updatedSpeed) {
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

