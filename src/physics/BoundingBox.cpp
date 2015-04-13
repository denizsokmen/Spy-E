#include <vector>

#include "physics/BoundingBox.h"
#include "physics/Face.h"

BoundingBox::BoundingBox(std::vector<glm::vec3> vertices) {
    this->vertices = vertices;
    this->createFromVertices();
    this->createFaces();
}

void BoundingBox::createFromVertices(){

    float xmax = -1000.0;
    float xmin = 1000.0;
    float ymax = -1000.0;
    float ymin = 1000.0;
    float zmax = -1000.0;
    float zmin = 1000.0;

    for(int i = 0; i < vertices.size(); i++){

        glm::vec3 vertex = vertices[i];

        if(vertex.x > xmax) xmax = vertex.x;
        if(vertex.x < xmin) xmin = vertex.x;

        if(vertex.y > ymax) ymax = vertex.y;
        if(vertex.y < ymin) ymin = vertex.y;

        if(vertex.z > zmax) zmax = vertex.z;
        if(vertex.z < zmin) zmin = vertex.z;
    }
    minVertex = glm::vec3(xmin, ymin, zmin);
    maxVertex = glm::vec3(xmax, ymax, zmax);

    width = abs(minVertex.x - maxVertex.x);
    height = abs(minVertex.y - maxVertex.y);
    depth = abs(minVertex.z - maxVertex.z);
}

void BoundingBox::update(glm::vec3 position) {
  //  minVertex = glm::vec3(position.x - width/2, position.y - height/2, position.z - depth/2);
    //maxVertex = glm::vec3(position.x + width/2, position.y + height/2, position.z + depth/2);

}

void BoundingBox::createFaces() {
    //seven points are required

    glm::vec3 firstPoint = minVertex;
    glm::vec3 secondPoint = glm::vec3(minVertex.x, minVertex.y, minVertex.z + depth);
    glm::vec3 thirdPoint = glm::vec3(secondPoint.x, secondPoint.y - height, secondPoint.z);
    glm::vec3 fourthPoint = maxVertex;
    glm::vec3 fifthPoint = glm::vec3(maxVertex.x, maxVertex.y, maxVertex.z - depth);
    glm::vec3 sixthPoint = glm::vec3(fifthPoint.x + width, fifthPoint.y + height, fifthPoint.z);


    faces.push_back(new Face(firstPoint, secondPoint, thirdPoint));
    faces.push_back(new Face(secondPoint, thirdPoint, fourthPoint));
    faces.push_back(new Face(fifthPoint, sixthPoint, fourthPoint));
    faces.push_back(new Face(fifthPoint, sixthPoint, firstPoint));
    faces.push_back(new Face(fifthPoint, thirdPoint, fourthPoint));
    faces.push_back(new Face(firstPoint, secondPoint, sixthPoint));
}


glm::vec3 BoundingBox::getMaxVertex(){
    return maxVertex;
}

glm::vec3 BoundingBox::getMinVertex(){
    return minVertex;
}

BoundingBox::~BoundingBox() { }

