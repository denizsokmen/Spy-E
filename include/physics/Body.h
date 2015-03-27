#ifndef BODY_H_INC
#define BODY_H_INC

#include <glm/glm.hpp>
#include "physics/BoundingBox.h"
#include <vector>

class Body{

    bool isCollided;
    glm::vec3 *location;
    glm::vec3 speed;
    glm::vec3 acceleration;
    std::vector<glm::vec3> vertices;
    BoundingBox *boundingBox;

public:

    Body(glm::vec3 *loc, glm::vec3 speed, glm::vec3 acc, std::vector<glm::vec3> vertices);
    ~Body();

    void setIsCollided(bool);
    bool getIsCollided();
    void setLocation(glm::vec3 loc);
    void setSpeed(glm::vec3 speed);
    void setSpeed(float speed, char direction);
    glm::vec3 getAcceleration();
    glm::vec3 getSpeed();
    glm::vec3 getLocation();
    std::vector<glm::vec3> getVertices();
    BoundingBox* getBoundingBox();
    void updateBoundingBox(std::vector<glm::vec3> v);
};
#endif
