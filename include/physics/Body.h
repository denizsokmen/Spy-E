#ifndef BODY_H_INC
#define BODY_H_INC

#include <glm/glm.hpp>
#include "physics/BoundingBox.h"
#include <vector>

class Body{

    glm::vec3 location;
    glm::vec3 speed;
    glm::vec3 acceleration;
    BoundingBox *boundingBox;

public:
    Body(glm::vec3 loc, glm::vec3 speed, glm::vec3 acc);
    ~Body();

    void setLocation(glm::vec3 loc);
    void setSpeed(glm::vec3 speed);
    glm::vec3 getAcceleration();
    glm::vec3 getSpeed();
    glm::vec3 getLocation();
    BoundingBox* getBoundingBox();
};
#endif
