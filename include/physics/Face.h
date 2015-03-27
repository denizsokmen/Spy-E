#ifndef SPYE_FACE_H
#define SPYE_FACE_H

#include <glm/glm.hpp>

class Face {


public:
    glm::vec3 firstPoint;
    glm::vec3 secondPoint;
    glm::vec3 thirdPoint;

    Face(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint);

    ~Face();

    bool intersects(glm::vec3 direction, glm::vec3 origin);


};


#endif //SPYE_FACE_H
