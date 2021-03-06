#ifndef PHYSICSWORLD_H_INC
#define PHYSICSWORLD_H_INC

#include <vector>
#include "Body.h"
#include "include/world/Entity.h"

class Body;
class Entity;
class BoundingBox;
class Physics;

class PhysicsWorld{

    std::vector<Body*> bodies;
    Physics *physics;

public:
    PhysicsWorld(Physics*);
    ~PhysicsWorld();

    bool bounce;

    Body* createBody(Entity* bodyEntity, std::vector<glm::vec3> vertices);
    void update(float dt);
    bool isCollided(Body *b1, Body *b2);
    std::vector<Body*> getBodies();

    glm::vec3 getUpdatedSpeed(float dt, glm::vec3 &acceleration, glm::vec3 &speed);

    glm::vec3 getUpdatedLocation(float dt, glm::vec3 &acceleration, glm::vec3 &location, glm::vec3 &updatedSpeed);

    void applyAirFriction(Body *body);
};
#endif