//
// Created by Deniz Sokmen on 24/04/15.
//

#ifndef SPYE_SKELETON_H
#define SPYE_SKELETON_H

#include <graphics/Bone.h>
#include <vector>

class Skeleton {
public:
    std::vector<Bone> bones;
    Bone *rootBone;
    void buildPoses();
    void buildTransforms();

};

#endif //SPYE_SKELETON_H
