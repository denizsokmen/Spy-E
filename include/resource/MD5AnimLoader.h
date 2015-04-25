//
// Created by Deniz Sokmen on 24/04/15.
//

#ifndef SPYE_MD5ANIMLOADER_H
#define SPYE_MD5ANIMLOADER_H
#include <graphics/Skeleton.h>
#include <string>
#include <glm/glm.hpp>
#include <graphics/AnimationState.h>

class MD5Anim {
public:

    MD5Anim();
    ~MD5Anim();
    AnimationState* loadAnim(std::string fname);
    void update(float deltaTime);
    void render();

    //Default frame
    Skeleton baseSkeleton;
    //Interpolated, current frame.
    Skeleton currentSkeleton;
    //Skeletons of all frames.
    std::vector<Skeleton> frameSkeleton;

    struct BoneInfo {
        int parent;
        int flags;
        int index;
    };

    std::vector<BoneInfo> boneInfos;

    struct FrameData {
        int id;
        std::vector<float> data;
    };

    struct Bound
    {
        glm::vec3   min;
        glm::vec3   max;
    };

    std::vector<Bound> bounds;

    std::vector<glm::mat4> boneMatrix;
    void buildFrames(FrameData &data);
    void interpolateSkeletons(Skeleton &finalskel, Skeleton &sk0, Skeleton &sk1, float intrp);
private:
    int animatedParts;
    int frameRate;
    int numFrames;
    int numJoints;

    float animTime;
    float animDuration;
    float frameDuration;

    void calcQuatW(glm::quat &quat);
};

#endif //SPYE_MD5ANIMLOADER_H
