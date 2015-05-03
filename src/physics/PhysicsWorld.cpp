#include "physics/PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(Physics* physics){
    this->physics = physics;
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
                        if (body->getLocation().y < 2.1f) {
                            body->setLocation(2.5f, 'y');
                            body->setAcceleration(0, 'y');
                            body->setSpeed(0, 'y');
                            if(bounce)
                                body->setSpeed(-(body->getSpeed().y), 'y');
                            else
                                body->setSpeed(0, 'y');

                        } else {
                            body->setSpeed(0, 'x');
                            body->setSpeed(0, 'z');

                        }
                    }
                }
            }
        }
    }
}

void PhysicsWorld::applyAirFriction(Body *body) {
    //body->addAcceleration(-(body->getSpeed().x)/2, 'x');
    //body->addAcceleration(-(body->getSpeed().z)/2, 'z');
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

    return ( box1->getMaxVertex().x + b1->getLocation().x > box2->getMinVertex().x + b2->getLocation().x &&
            box1->getMinVertex().x + b1->getLocation().x < box2->getMaxVertex().x + b2->getLocation().x &&
            box1->getMaxVertex().y + b1->getLocation().y > box2->getMinVertex().y + b2->getLocation().y &&
            box1->getMinVertex().y + b1->getLocation().y < box2->getMaxVertex().y + b2->getLocation().y &&
            box1->getMaxVertex().z + b1->getLocation().z > box2->getMinVertex().z + b2->getLocation().z &&
            box1->getMinVertex().z + b1->getLocation().z < box2->getMaxVertex().z + b2->getLocation().z  );
}

std::vector<Body *> PhysicsWorld::getBodies() {
    return this->bodies;
}
