//
// Created by Deniz Sokmen on 24/04/15.
//

#include <resource/MD5AnimLoader.h>
#include <math.h>
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <graphics/AnimationState.h>
#include <string.h>

MD5Anim::MD5Anim() {

}

MD5Anim::~MD5Anim() {
}

void MD5Anim::calcQuatW(glm::quat& quat) {
    //In MD5 models, you need to calculate w of
    //each quaternion.
    float t = 1.0f- (quat.x * quat.x) - (quat.y * quat.y) - (quat.z * quat.z);
    if (t < 0.0f)
        quat.w = 0.0f;
    else
        quat.w = -sqrtf(t);
}

void MD5Anim::buildFrames(FrameData& data) {
    //Build a skeleton using frame data and add
    //it to frame skeleton list.
    Skeleton skeleton;
    skeleton.bones.reserve(boneInfos.size());
    for (unsigned int i=0; i < boneInfos.size(); i ++ ) {
        int j=0;
        BoneInfo &info = boneInfos[i];
        Bone newBone = baseSkeleton.bones[i];

        newBone.parentID = info.parent;

        //Apply differences between default bone and
        //the new.
        if (info.flags & 1)
            newBone.localPos.x = data.data[info.index + j++];
        if (info.flags & 2)
			newBone.localPos.y = data.data[info.index + j++];
        if (info.flags & 4)
			newBone.localPos.z = data.data[info.index + j++];
        if (info.flags & 8)
            newBone.localRotation.x = data.data[info.index + j++];
        if (info.flags & 16)
            newBone.localRotation.y = data.data[info.index + j++];
        if (info.flags & 32)
            newBone.localRotation.z = data.data[info.index + j++];

		newBone.localPos.x *= scaleamount.x;
		newBone.localPos.y *= scaleamount.y;
		newBone.localPos.z *= scaleamount.z;


        calcQuatW(newBone.localRotation);

        //Add bone to the skeleton.
        skeleton.bones.push_back(newBone);
    }
    //So far we have been calculating in joint-space
    //convert everything to the model space.
    skeleton.buildTransforms();

    //Add the skeleton.
    frameSkeleton.push_back(skeleton);
}

void MD5Anim::interpolateSkeletons(Skeleton &finalskel, Skeleton &sk0, Skeleton &sk1, float intrp) {
    //Most important part of the animation is to
    //interpolate between two skeletons(frames) to
    //get smoother final skeleton.
    for (int i=0; i < numJoints; i++) {

        Bone& finalBone = finalskel.bones[i];
        Bone& bone0 = sk0.bones[i];
        Bone& bone1 = sk1.bones[i];

        finalBone.parentID = bone0.parentID;

        //Linear and spherical interpolation.
        finalBone.worldPos = bone0.worldPos + (bone1.worldPos - bone0.worldPos)* intrp;
        finalBone.worldRotation = glm::slerp(bone0.worldRotation, bone1.worldRotation, intrp);



        glm::mat4 translation = glm::translate(glm::mat4(1.0f), finalBone.worldPos);
        glm::mat4 rotation = glm::toMat4(finalBone.worldRotation);
        //This is what we need, to calculate offset matrices
        //so we can upload them to GPU and transform the vertices.
        boneMatrix[i] = translation * rotation;
    }
}

void MD5Anim::update(float deltaTime) {
    animTime += deltaTime;
    while (animTime > animDuration) animTime -= animDuration;
    while (animTime < 0.0f ) animTime += animDuration;

    float frameNum = animTime * (float) frameRate;
    int frame0 = (int) floorf( frameNum );
    int frame1 = (int) ceilf( frameNum );
    frame0 %= numFrames;
    frame1 %= numFrames;

    float intrp = fmodf(animTime, frameDuration);
    interpolateSkeletons(currentSkeleton, frameSkeleton[frame0],
                         frameSkeleton[frame1], intrp);
}


AnimationState* MD5Anim::loadAnim(std::string fname, glm::vec3&& scale, glm::quat&& rotate) {
	rotationamount = rotate;
	scaleamount = scale;
    FILE *f;
    char data[512];
    f=fopen(fname.c_str(),"rb");
    int frameind;
    char junk[100];
    AnimationState *anim = new AnimationState();
    while(!feof(f))
    {
        fgets(data,sizeof(data),f);

        if (sscanf(data," numFrames %d", &numFrames) == 1)
        {
            printf("numframes: %d\n", numFrames);
            anim->numFrames = numFrames;
            if (numFrames > 0)
            {
                frameSkeleton.reserve(numFrames);
                bounds.reserve(numFrames);
            }

        }
        else if(sscanf(data," numJoints %d", &numJoints) == 1)
        {
            printf("numjoints: %d\n", numJoints);
            anim->numJoints = numJoints;
            boneInfos.reserve(numJoints);
            baseSkeleton.bones.reserve(numJoints);
            boneMatrix.resize(numJoints);
            currentSkeleton.bones.resize(numJoints);
        }

        else if (sscanf(data," frameRate %d", &frameRate) == 1)
        {
            anim->frameRate = frameRate;

            printf("framerate: %d\n", frameRate);

        }
        else if (sscanf(data," numAnimatedComponents %d", &animatedParts) == 1)
        {
            anim->animatedParts = animatedParts;

            printf("animatedparts: %d\n", animatedParts);
        }
        else if (strncmp(data,"hierarchy {", 11) == 0)
        {
            for (int i=0; i < numJoints; i++)
            {
                fgets(data, sizeof(data),f);
                BoneInfo info;
                sscanf(data, " \"%[^\"]\" %d %d %d", junk,&info.parent, &info.flags,
                       &info.index);

                printf("junk %s %d %d %d\n", junk, info.parent, info.flags, info.index);
                boneInfos.push_back(info);
            }

        }
        else if (strncmp(data,"bounds {", 8) == 0)
        {
            for (int i=0; i < numFrames; i++)
            {
                Bound bound;
                fgets(data,sizeof(data),f);
                sscanf(data," ( %f %f %f ) ( %f %f %f )", &bound.min.x, &bound.min.y, &bound.min.z, &bound.max.x, &bound.max.y, &bound.max.z);
                bounds.push_back(bound);
            }

        }
        else if (strncmp(data, "baseframe {", 11) == 0)
        {
            for (int i=0; i < numJoints; i++ )
            {
                fgets(data,sizeof(data),f);
                Bone bon;
                if (sscanf(data," ( %f %f %f ) ( %f %f %f )", &bon.localPos.x, &bon.localPos.y, &bon.localPos.z, &bon.localRotation.x, &bon.localRotation.y, &bon.localRotation.z) == 6)
                {
                    calcQuatW(bon.localRotation);
					//bon.localPos.x *= scale.x;
					//bon.localPos.y *= scale.y;
					//bon.localPos.z *= scale.z;
                    baseSkeleton.bones.push_back(bon);
                }
            }
        }
        else if (sscanf( data, " frame %d", &frameind) == 1)
        {
            FrameData fData;
            for (int i=0; i < animatedParts; i++)
            {
                float frmData;
                fscanf(f, "%f", &frmData);
                fData.data.push_back(frmData);
            }
            buildFrames(fData);
            //build skeleton
        }
    }
    fclose(f);

    anim->baseSkeleton = baseSkeleton;
    for(auto it: frameSkeleton) {
        anim->frameSkeleton.push_back(it);
    }
    fprintf(stdout, "Anim successful \n");
    anim->frameDuration=1.0f / (float)frameRate;
	anim->animDuration = anim->frameDuration * (float)numFrames;
    anim->animTime=0.0f;

    return anim;

}
