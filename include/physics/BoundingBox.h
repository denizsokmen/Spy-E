#ifndef BOUNDINGBOX_H_INC
#define BOUNDINGBOX_H_INC

#include <glm/glm.hpp>
#include <vector>

class Face;

class BoundingBox{

    std::vector<glm::vec3> vertices;
    std::vector<Face *> faces;



public:
    BoundingBox(std::vector<glm::vec3> vertices);
    ~BoundingBox();

    glm::vec3 minVertex;
    glm::vec3 maxVertex;
    float depth;
    float width;
    float height;

    glm::vec3 getMinVertex();
    glm::vec3 getMaxVertex();


private:
    void createFromVertices();

    void createFaces();

};
#endif