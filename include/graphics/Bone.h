//
// Created by Deniz Sokmen on 24/04/15.
//

#ifndef SPYE_BONE_H
#define SPYE_BONE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Bone {
public:
    bool isUpdated;
    int parentID;
    void setTransformation(glm::vec3 pos, glm::quat rot);
    glm::mat4 toMatrix();

    glm::mat4 transformation;

    glm::vec3 localPos;
    glm::vec3 worldPos;

    glm::quat localRotation;
    glm::quat worldRotation;

    glm::mat4 inverseBindPose;
};


#endif //SPYE_BONE_H
