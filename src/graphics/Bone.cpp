//
// Created by Deniz Sokmen on 24/04/15.
//
#include <graphics/Bone.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void Bone::setTransformation(glm::vec3 pos, glm::quat rot) {
    //Set default transformation for the bone

    localPos = pos;
    worldPos = pos;

    localRotation = rot;
    worldRotation = rot;

    isUpdated = true;
}

glm::mat4 Bone::toMatrix() {
    if (isUpdated) {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), worldPos);
        glm::mat4 rotation = glm::toMat4(worldRotation);
        transformation = translation * rotation;
    }

    return transformation;
}