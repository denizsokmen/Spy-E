#ifndef BODY_H_INC
#define BODY_H_INC

#include <glm/glm.hpp>
#include "physics/BoundingBox.h"
#include <vector>
#include <tests/physics/TestPhysics.h>
#include "include/world/Entity.h"

class Entity;

class Body{

    Entity* entity;
    glm::vec3 *location;
    glm::vec3 speed;
    glm::vec3 acceleration;
    std::vector<glm::vec3> vertices;
    BoundingBox *boundingBox;

public:

    Body(Entity* bodyEntity, std::vector<glm::vec3> v);
    ~Body();

    void setLocation(glm::vec3 loc);
    void setLocation(float location, char direction);
    void setSpeed(glm::vec3 speed);
    void setSpeed(float speed, char direction);
    void setAcceleration(glm::vec3 acceleration);
    void setAcceleration(float acceleration, char direction);
    void addAcceleration(float acceleration, char direction);
    Entity* getEntity();
    glm::vec3 getAcceleration();
    glm::vec3 getSpeed();
    glm::vec3 getLocation();
    std::vector<glm::vec3> getVertices();
    BoundingBox* getBoundingBox();
    BoundingBox* getBoundingBoxFromLocation();
};
#endif
