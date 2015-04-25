//
// Created by deniz on 23/04/15.
//

#ifndef SPYE_MD5LOADER_H
#define SPYE_MD5LOADER_H
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <graphics/Skeleton.h>

class Mesh;

class SkeletalMesh {
public:
    SkeletalMesh();
    ~SkeletalMesh();

    struct Vertex {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec2 uv;
        glm::vec4 boneIndex;
        glm::vec4 bias;
    };
    std::vector<Vertex> vertices;

    struct Triangle {
        int index[3];
    };

    std::vector<Triangle> indices;

    struct Weight {
        glm::vec3 pos;
        float bias;
        int boneIndex;
    };
    std::vector<Weight> weights;

    struct WeightInfo {
        //Weight info for each vertex.
        //In a separate struct for compatibility.
        int weightCount;
        int weightOffset;
    };
    std::vector<WeightInfo> weightInfos;


    void generateTangents();
};

class MD5Loader {

public:
    MD5Loader();
    ~MD5Loader();

    Mesh* load(std::string name);

    void transformNormals(SkeletalMesh &mesh);

    void transformMesh(SkeletalMesh &mesh, Skeleton* skeleton);

    void calcQuatW(glm::quat &quat);

};

#endif //SPYE_MD5LOADER_H
