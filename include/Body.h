#ifndef BODY_H_INC
#define BODY_H_INC

#include <glm/glm.hpp>
#include <vector>

class Body{

    glm::vec3 location;
    glm::vec3 speed;
    glm::vec3 acceleration;

public:
    Body(glm::vec3 loc, glm::vec3 speed, glm::vec3 acc);
    ~Body();

};
#endif
