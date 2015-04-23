//
// Created by deniz on 23/04/15.
//

#include <stdexcept>
#include "resource/MD5Loader.h"
#include <glm/glm.hpp>
#include <vector>
#include <string.h>
#include <glm/gtc/quaternion.hpp>

#if 0
Mesh *MD5Loader::load(std::string name) {

    FILE *f;
    char data[512];

    f=fopen(name.c_str(),"rb");

    if (f == NULL) {
        throw std::runtime_error("Error loading file");
    }

    std::vector<glm::mat4> boneMatrix;

    int ver,curMesh=0;
    Shader *shd;


    bindSkeleton = new Skeleton();
    bindSkeleton->bones.clear();
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
            if (numJoints > 0)
            {
                boneMatrix.resize(numJoints);
                bindSkeleton->bones.reserve(numJoints);

            }
        }
        else if (sscanf(data," numMeshes %d", &numMeshes) == 1)
        {
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
                if (sscanf (data,"%s %d ( %f %f %f ) ( %f %f %f )",junk,&bone.parentID,
                            &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z) == 8)
                {
                    utils::calcQuatW(rot);
                    bone.setTransformation(pos,rot);
                    bindSkeleton->bones.push_back(bone);

                }
            }
            bindSkeleton->buildPoses();

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
                    Bitmap *bmp=new TGATexture();
                    bmp->load(fname);
                    ms.tex.createFromBitmap(bmp);
                    delete bmp;

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
                else if (sscanf (data," vert %d ( %f %f ) %d %d", &vert_index, &fdata[0], &fdata[1],
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
                else if (sscanf (data," tri %d %d %d %d",&tri_index,&idata[0],&idata[1],&idata[2]) == 4)
                {
                    SkeletalMesh::Triangle tri;
                    tri.index[0]=idata[0];
                    tri.index[1]=idata[1];
                    tri.index[2]=idata[2];
                    ms.indices.push_back(tri);
                }
                else if (sscanf (data," weight %d %d %f ( %f %f %f )",
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

            transformMesh(ms);
            transformNormals(ms);
            ms.loadShader(shd);
            ms.createVBO();
            meshes.push_back(ms);
            curMesh++;
        }
    }
    fclose(f);
    fprintf(stdout, "Model successful \n");
}
#endif