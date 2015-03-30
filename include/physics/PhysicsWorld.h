#ifndef PHYSICSWORLD_H_INC
#define PHYSICSWORLD_H_INC
#include <vector>
#include "Body.h"

class PhysicsWorld{

    std::vector<Body*> bodies;

public:
    PhysicsWorld();
    ~PhysicsWorld();

    float floorY;

    bool bounce;

    Body* createBody(glm::vec3 *loc, glm::vec3 speed, glm::vec3 acc, std::vector<glm::vec3> v);
    void update(float dt);
    bool isCollided(Body *b1, Body *b2);
    bool isCollidedX(Body *b1, Body *b2);
    bool isCollidedY(Body *b1, Body *b2);
    bool isCollidedZ(Body *b1, Body *b2);

    glm::vec3 getUpdatedSpeed(float dt, glm::vec3 &acceleration, glm::vec3 &speed);

    glm::vec3 getUpdatedLocation(float dt, glm::vec3 &acceleration, glm::vec3 &location, glm::vec3 &updatedSpeed);

    void applyAirFriction(Body *body);
};
#endif