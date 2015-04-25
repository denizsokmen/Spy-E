//
// Created by deniz on 23/04/15.
//

#include <stdexcept>
#include "resource/MD5Loader.h"
#include <glm/glm.hpp>
#include <vector>
#include <string.h>
#include <glm/gtc/quaternion.hpp>
#include <graphics/VertexBuffer.h>
#include <graphics/SubMesh.h>
#include <resource/ResourceManager.h>
#include <graphics/Material.h>
#include <graphics/Mesh.h>

void MD5Loader::calcQuatW(glm::quat& quat) {
    //In MD5 models, you need to calculate w of
    //each quaternion.
    float t = 1.0f- (quat.x * quat.x) - (quat.y * quat.y) - (quat.z * quat.z);
    if (t < 0.0f)
        quat.w = 0.0f;
    else
        quat.w = -sqrtf(t);
}

void MD5Loader::transformMesh(SkeletalMesh& mesh, Skeleton* skeleton) {
    //Bones' positions are insufficient alone, we must
    //combine them with their weights to get model space
    //vertices at bind pose, which are enough for GPU.
    for (unsigned int i = 0; i < mesh.vertices.size(); i ++) {
        SkeletalMesh::Vertex & vert = mesh.vertices[i];
        SkeletalMesh::WeightInfo &winfo = mesh.weightInfos[i];
        vert.pos = glm::vec3(0);
        vert.normal = glm::vec3(0);
        vert.boneIndex = glm::vec4(0);
        vert.bias = glm::vec4(0);

        for (int j = 0; j < std::min(4, winfo.weightCount); j++) {
            SkeletalMesh::Weight &weight = mesh.weights[winfo.weightOffset + j];
            Bone &bone = skeleton->bones[weight.boneIndex];

            //bone space -> model space
            glm::vec3 rotatedP = bone.worldRotation * weight.pos;
            vert.pos += (bone.worldPos + rotatedP) * weight.bias;
            vert.boneIndex[j] = weight.boneIndex;
            vert.bias[j] = weight.bias;
        }
    }
}

void MD5Loader::transformNormals(SkeletalMesh& mesh) {
    //Since MD5 models don't support built-in normals
    //we calculate them ourselves.
    for (unsigned int i = 0; i < mesh.indices.size(); i++) {
        glm::vec3 v0 = mesh.vertices[mesh.indices[i].index[0]].pos;
        glm::vec3 v1 = mesh.vertices[mesh.indices[i].index[1]].pos;
        glm::vec3 v2 = mesh.vertices[mesh.indices[i].index[2]].pos;

        glm::vec3 normal = glm::cross(v2-v0, v1-v0);

        mesh.vertices[mesh.indices[i].index[0]].normal += normal;
        mesh.vertices[mesh.indices[i].index[1]].normal += normal;
        mesh.vertices[mesh.indices[i].index[2]].normal += normal;
    }

    //normalize all normals
    for (unsigned int i = 0; i < mesh.vertices.size(); i++) {
        SkeletalMesh::Vertex& vertex = mesh.vertices[i];
        vertex.normal = glm::normalize(vertex.normal);
    }
}


void SkeletalMesh::generateTangents()
{
    Triangle *pTriangle = 0;
    Vertex *pVertex0 = 0;
    Vertex *pVertex1 = 0;
    Vertex *pVertex2 = 0;
    float edge1[3] = {0.0f, 0.0f, 0.0f};
    float edge2[3] = {0.0f, 0.0f, 0.0f};
    float texEdge1[2] = {0.0f, 0.0f};
    float texEdge2[2] = {0.0f, 0.0f};
    float tangent[3] = {0.0f, 0.0f, 0.0f};
    float bitangent[3] = {0.0f, 0.0f, 0.0f};
    float det = 0.0f;
    float nDotT = 0.0f;
    float bDotB = 0.0f;
    float length = 0.0f;
    int totalVertices = vertices.size();
    int totalTriangles = indices.size();

    // Initialize all the vertex tangents and bitangents.
    for (int i = 0; i < totalVertices; ++i)
    {
        pVertex0 = &vertices[i];

        pVertex0->tangent[0] = 0.0f;
        pVertex0->tangent[1] = 0.0f;
        pVertex0->tangent[2] = 0.0f;

    }

    // Calculate the vertex tangents and bitangents.
    for (int i = 0; i < totalTriangles; ++i)
    {
        pTriangle = &indices[i];

        pVertex0 = &vertices[pTriangle->index[0]];
        pVertex1 = &vertices[pTriangle->index[1]];
        pVertex2 = &vertices[pTriangle->index[2]];

        // Calculate the triangle face tangent and bitangent.

        edge1[0] = pVertex1->pos[0] - pVertex0->pos[0];
        edge1[1] = pVertex1->pos[1] - pVertex0->pos[1];
        edge1[2] = pVertex1->pos[2] - pVertex0->pos[2];

        edge2[0] = pVertex2->pos[0] - pVertex0->pos[0];
        edge2[1] = pVertex2->pos[1] - pVertex0->pos[1];
        edge2[2] = pVertex2->pos[2] - pVertex0->pos[2];

        texEdge1[0] = pVertex1->uv[0] - pVertex0->uv[0];
        texEdge1[1] = pVertex1->uv[1] - pVertex0->uv[1];

        texEdge2[0] = pVertex2->uv[0] - pVertex0->uv[0];
        texEdge2[1] = pVertex2->uv[1] - pVertex0->uv[1];

        det = texEdge1[0] * texEdge2[1] - texEdge2[0] * texEdge1[1];

        if (fabs(det) < 1e-6f)
        {
            tangent[0] = 1.0f;
            tangent[1] = 0.0f;
            tangent[2] = 0.0f;

            bitangent[0] = 0.0f;
            bitangent[1] = 1.0f;
            bitangent[2] = 0.0f;
        }
        else
        {
            det = 1.0f / det;

            tangent[0] = (texEdge2[1] * edge1[0] - texEdge1[1] * edge2[0]) * det;
            tangent[1] = (texEdge2[1] * edge1[1] - texEdge1[1] * edge2[1]) * det;
            tangent[2] = (texEdge2[1] * edge1[2] - texEdge1[1] * edge2[2]) * det;

            bitangent[0] = (-texEdge2[0] * edge1[0] + texEdge1[0] * edge2[0]) * det;
            bitangent[1] = (-texEdge2[0] * edge1[1] + texEdge1[0] * edge2[1]) * det;
            bitangent[2] = (-texEdge2[0] * edge1[2] + texEdge1[0] * edge2[2]) * det;
        }

        // Accumulate the tangents and bitangents.

        pVertex0->tangent[0] += tangent[0];
        pVertex0->tangent[1] += tangent[1];
        pVertex0->tangent[2] += tangent[2];

        pVertex1->tangent[0] += tangent[0];
        pVertex1->tangent[1] += tangent[1];
        pVertex1->tangent[2] += tangent[2];

        pVertex2->tangent[0] += tangent[0];
        pVertex2->tangent[1] += tangent[1];
        pVertex2->tangent[2] += tangent[2];
    }

    // Orthogonalize and normalize the vertex tangents.
    for (int i = 0; i < totalVertices; ++i)
    {
        pVertex0 = &vertices[i];

        // Gram-Schmidt orthogonalize tangent with normal.

        nDotT = pVertex0->normal[0] * pVertex0->tangent[0] +
                pVertex0->normal[1] * pVertex0->tangent[1] +
                pVertex0->normal[2] * pVertex0->tangent[2];

        pVertex0->tangent[0] -= pVertex0->normal[0] * nDotT;
        pVertex0->tangent[1] -= pVertex0->normal[1] * nDotT;
        pVertex0->tangent[2] -= pVertex0->normal[2] * nDotT;

        // Normalize the tangent.

        length = 1.0f / sqrtf(pVertex0->tangent[0] * pVertex0->tangent[0] +
                              pVertex0->tangent[1] * pVertex0->tangent[1] +
                              pVertex0->tangent[2] * pVertex0->tangent[2]);

        pVertex0->tangent[0] *= length;
        pVertex0->tangent[1] *= length;
        pVertex0->tangent[2] *= length;
    }

}


Mesh *MD5Loader::load(std::string name) {

    FILE *f;
    char data[512];

    f=fopen(name.c_str(),"rb");

    if (f == NULL) {
        throw std::runtime_error("Error loading file");
    }

    std::string filename = name.c_str();
    std::string::size_type offset = filename.find_last_of('\\');
    std::string directoryPath;
    if (offset != std::string::npos)
    {
        directoryPath = filename.substr(0, ++offset);
    }
    else
    {
        offset = filename.find_last_of('/');

        if (offset != std::string::npos)
            directoryPath = filename.substr(0, ++offset);
    }

    std::vector<glm::mat4> boneMatrix;

    int ver,curMesh=0;

    Mesh *mesh = new Mesh();
    const char *exts[5]= {".jpg", ".png", ".tga", ".bmp", ""};



    Skeleton *bindSkeleton = new Skeleton();
    bindSkeleton->bones.clear();

    std::vector<SkeletalMesh> meshes;
    meshes.clear();

    int numJoints;
    int numMeshes;

    while(!feof(f))
    {
        fgets(data,sizeof(data),f);

        if (sscanf(data," MD5Version %d", &ver) == 1)
        {

        }
        else if (sscanf(data," numJoints %d", &numJoints) == 1)
        {
            printf("numJoints %d\n", numJoints);
            if (numJoints > 0)
            {
                boneMatrix.resize(numJoints);
                bindSkeleton->bones.reserve(numJoints);

            }
        }
        else if (sscanf(data," numMeshes %d", &numMeshes) == 1)
        {
            printf("nummeshes %d\n", numMeshes);
            if (numMeshes > 0)
            {
                meshes.reserve(numMeshes);

            }
        }
        else if (strncmp(data,"joints {",8) == 0)
        {
            for (int i = 0; i < numJoints; ++i)
            {
                Bone bone;
                char junk[100];
                glm::vec3 pos;
                glm::quat rot;
                fgets(data,sizeof(data),f);
                sscanf (data," \"%[^\"]\" %d ( %f %f %f ) ( %f %f %f ) ",junk,&bone.parentID,
                            &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z);

                    calcQuatW(rot);
                    bone.setTransformation(pos,rot);
                    bindSkeleton->bones.push_back(bone);


            }
            bindSkeleton->buildPoses();
            mesh->setSkeleton(bindSkeleton);

        }
        else if (strncmp(data,"mesh {",6) == 0)
        {
            SkeletalMesh ms;
            int numVert= 0;
            int numTris = 0;
            int numWeights = 0;
            int vert_index = 0;
            int tri_index = 0;
            int weight_index = 0;
            float fdata[4];
            int idata[3];
            char fname[64];
            VertexBuffer* vertexBuffer = new VertexBuffer();
            Material* material = new Material();
            Texture* texture = NULL;
            material->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
            material->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
            material->specular = glm::vec3(0.0f, 0.0f, 0.0f);
            material->shininess = 0.3f;
            material->dissolve = 1.0f;
            material->program = ResourceManager::instance()->createShader("./shaders/generic_bone").get();



            while (data[0] != '}' && !feof(f))
            {
                fgets(data,sizeof(data),f);

                if (strstr(data,"shader "))
                {
                    int qu=0;
                    int go=0;
                    for (unsigned int u = 0; u < sizeof (data) && (qu < 2); ++u)
                    {
                        if (data[u] == '\"')
                            qu++;

                        if ((qu == 1) && (data[u] != '\"'))
                        {
                            fname[go] = data[u];
                            go++;
                        }
                    }
                    fname[go]='\0';

                    std::string fNameStr = fname;
                    std::string::size_type fOffset = fNameStr.find_last_of('\\');

                    if (fOffset != std::string::npos)
                    {
                        fNameStr = fNameStr.substr(++fOffset);
                    }
                    else
                    {
                        fOffset = fNameStr.find_last_of('/');

                        if (fOffset != std::string::npos)
                            fNameStr = fNameStr.substr(++fOffset);
                    }

                    printf("FILE: %s\n", fNameStr.c_str());

                    for(int i = 0; i < 5; i++) {

                        if (ResourceManager::instance()->createTexture(directoryPath + fNameStr + std::string(exts[i])) != NULL) {

                            material->setTexture(TEXTURE_DIFFUSE, ResourceManager::instance()->createTexture(directoryPath + fNameStr + std::string(exts[i])).get());
                            break;
                        }
                    }

                    /*Bitmap *bmp=new TGATexture();
                    bmp->load(fname);
                    ms.tex.createFromBitmap(bmp);
					
                    delete bmp;*/

                }
                else if (sscanf (data," numverts %d", &numVert) == 1)
                {
                    if (numVert > 0)
                    {
                        ms.vertices.reserve(numVert);
                    }

                }
                else if (sscanf (data," numtris %d", &numTris) == 1)
                {
                    if (numTris > 0)
                    {
                        ms.indices.reserve(numTris);
                    }
                }
                else if (sscanf (data," numweights %d", &numWeights) == 1)
                {
                    if (numWeights > 0)
                    {
                        ms.weights.reserve(numWeights);
                    }
                }
                else if (sscanf (data," vert %d ( %f %f ) %d %d ", &vert_index, &fdata[0], &fdata[1],
                                 &idata[0], &idata[1]) == 5)
                {
                    SkeletalMesh::Vertex vert;
                    vert.uv.x = fdata[0];
                    vert.uv.y = fdata[1];
                    ms.vertices.push_back(vert);


                    SkeletalMesh::WeightInfo winfo;
                    winfo.weightOffset=idata[0];
                    winfo.weightCount=idata[1];
                    ms.weightInfos.push_back(winfo);

                }
                else if (sscanf (data," tri %d %d %d %d ",&tri_index,&idata[0],&idata[1],&idata[2]) == 4)
                {
                    SkeletalMesh::Triangle tri;
                    tri.index[0]=idata[0];
                    tri.index[1]=idata[1];
                    tri.index[2]=idata[2];
                    ms.indices.push_back(tri);
                }
                else if (sscanf (data," weight %d %d %f ( %f %f %f ) ",
                                 &weight_index, &idata[0], &fdata[0], &fdata[1],
                                 &fdata[2], &fdata[3]) == 6)
                {
                    SkeletalMesh::Weight wei;
                    wei.boneIndex=idata[0];
                    wei.bias=fdata[0];
                    wei.pos.x=fdata[1];
                    wei.pos.y=fdata[2];
                    wei.pos.z=fdata[3];
                    ms.weights.push_back(wei);
                }
            }

            transformMesh(ms, bindSkeleton);
            transformNormals(ms);
            ms.generateTangents();

            for (unsigned int i = 0; i < ms.vertices.size(); i ++) {
                SkeletalMesh::Vertex & vert = ms.vertices[i];
                vertexBuffer->addVertex(glm::vec3(vert.pos.x, vert.pos.y, vert.pos.z));
                vertexBuffer->addNormal(vert.normal);
                vertexBuffer->addTangent(vert.tangent);
                vertexBuffer->addUV(vert.uv);
                vertexBuffer->addWeight(vert.bias);
                vertexBuffer->addBoneIndex(vert.boneIndex);
            }

            for (unsigned int i = 0; i < ms.indices.size(); i++) {
                vertexBuffer->addIndex(ms.indices[i].index[0]);
                vertexBuffer->addIndex(ms.indices[i].index[1]);
                vertexBuffer->addIndex(ms.indices[i].index[2]);
            }

            vertexBuffer->upload();

            SubMesh *submesh = new SubMesh();
            submesh->mesh = mesh;
            submesh->vertexBuffer = vertexBuffer;
            submesh->material = material;
            submesh->triangleCount = 0;
            submesh->indexOffset = 0;
            mesh->subMeshes.push_back(submesh);


            meshes.push_back(ms);
            curMesh++;
        }
    }
    fclose(f);
    fprintf(stdout, "Model successful \n");
    return mesh;
}

SkeletalMesh::SkeletalMesh() {

}

SkeletalMesh::~SkeletalMesh() {

}

MD5Loader::MD5Loader() {

}

MD5Loader::~MD5Loader() {

}
