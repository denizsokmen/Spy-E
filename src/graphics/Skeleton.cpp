//
// Created by Deniz Sokmen on 24/04/15.
//
#include <graphics/Skeleton.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void Skeleton::buildPoses() {
    //We might need inverse bind poses for GPU.
    for (unsigned int i = 0; i < bones.size(); i++) {
        Bone& bone = bones[i];
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), bone.worldPos);
        glm::mat4 rotation = glm::toMat4(bone.worldRotation);
        glm::mat4 bind = translation * rotation;
        bone.inverseBindPose = glm::inverse(bind);
    }
}

void Skeleton::buildTransforms() {
    for (unsigned int i = 0; i < bones.size(); i++) {
        Bone& bone = bones[i];
        if (bone.parentID == -1) {
            //Parent bone is already in
            //model space.
            bone.worldRotation = bone.localRotation;
            bone.worldPos = bone.localPos;

        }
        else {
            //Conversion from joint space -> model space
            Bone& parent = bones[bone.parentID];
            bone.worldPos = (parent.worldRotation * bone.localPos)  +  parent.worldPos;
            bone.worldRotation = parent.worldRotation * bone.localRotation;
            bone.worldRotation = glm::normalize(bone.worldRotation);
            bone.setTransformation(bone.worldPos, bone.worldRotation);
        }
    }
}