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
                        printf("a");
                        if (body->getLocation().y <= 2.5f) {
                            body->setLocation(2.001f, 'y');
                            if(bounce)
                                body->setSpeed(-(body->getSpeed().y), 'y');
                            else
                                body->setSpeed(0, 'y');
                        } else {
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

    std::vector<glm::vec3> tempVertices1 = b1->getVertices();
    std::vector<glm::vec3> tempVertices2 = b2->getVertices();

    for(int i = 0; i < tempVertices1.size(); i++){
        tempVertices1[i].x += b1->getLocation().x;
        tempVertices1[i].y += b1->getLocation().y;
        tempVertices1[i].z += b1->getLocation().z;
    }

    for(int i = 0; i < tempVertices2.size(); i++){
        tempVertices2[i].x += b2->getLocation().x;
        tempVertices2[i].y += b2->getLocation().y;
        tempVertices2[i].z += b2->getLocation().z;
    }

    BoundingBox *tempBox1 = new BoundingBox(tempVertices1);
    BoundingBox *tempBox2 = new BoundingBox(tempVertices2);

    return ( tempBox1->getMaxVertex().x > tempBox2->getMinVertex().x &&
            tempBox1->getMinVertex().x < tempBox2->getMaxVertex().x &&
            tempBox1->getMaxVertex().y > tempBox2->getMinVertex().y &&
            tempBox1->getMinVertex().y < tempBox2->getMaxVertex().y &&
            tempBox1->getMaxVertex().z > tempBox2->getMinVertex().z &&
            tempBox1->getMinVertex().z < tempBox2->getMaxVertex().z   );

}

