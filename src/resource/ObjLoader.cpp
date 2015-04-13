#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <resource/tiny_obj_loader.h>

#include "resource/ObjLoader.h"
#include "graphics/VertexBuffer.h"
#include "resource/tiny_obj_loader.h"


VertexBuffer* ObjLoader::loadOBJ(const char * path) {
    printf("[ObjLoader] Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    std::ifstream inStream(path);
    if (!inStream) {
        printf("[ObjLoader] Impossible to open the file ! Are you in the right path ?\n");
        return NULL;
    }


    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;


    std::string err = tinyobj::LoadObj(shapes, materials, path);

    if (!err.empty()) {
        std::cerr << "[ObjLoader] [tinyobj] " << err << std::endl;
        exit(1);
    }


    std::cout << "[OBJLoader] # of shapes    : " << shapes.size() << std::endl;
    std::cout << "[OBJLoader] # of materials : " << materials.size() << std::endl;


    VertexBuffer* vertexBuffer = new VertexBuffer();


    for (size_t i = 0; i < shapes.size(); i++) {
        printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
        printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
        printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
        assert((shapes[i].mesh.indices.size() % 3) == 0);
        for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
            vertexBuffer->addIndex(shapes[i].mesh.indices[3*f+0]);
            vertexBuffer->addIndex(shapes[i].mesh.indices[3*f+1]);
            vertexBuffer->addIndex(shapes[i].mesh.indices[3*f+2]);
//            printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, , , , shapes[i].mesh.material_ids[f]);
        }

        printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
        printf("shape[%ld].normals: %ld\n", i, shapes[i].mesh.normals.size());
        printf("shape[%ld].texcoords: %ld\n", i, shapes[i].mesh.texcoords.size());
        assert((shapes[i].mesh.positions.size() % 3) == 0);
        assert((shapes[i].mesh.normals.size() % 3) == 0);
        for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
            glm::vec3 vertex  = glm::vec3(shapes[i].mesh.positions[3*v+0],
                                          shapes[i].mesh.positions[3*v+1],
                                          shapes[i].mesh.positions[3*v+2]);
            vertexBuffer->addVertex(vertex);

            glm::vec3 normal = glm::vec3(shapes[i].mesh.normals[3*v+0],
                                         shapes[i].mesh.normals[3*v+1],
                                         shapes[i].mesh.normals[3*v+2]);
            vertexBuffer->addNormal(normal);

            if (shapes[i].mesh.texcoords.size()) {
                glm::vec2 uv = glm::vec2(shapes[i].mesh.texcoords[2*v+0],
                                         shapes[i].mesh.texcoords[2*v+1]);
                vertexBuffer->addUV(uv);
            }


        }
    }



//    for (size_t i = 0; i < materials.size(); i++) {
//        printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
//        printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
//        printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
//        printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
//        printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
//        printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
//        printf("  material.Ns = %f\n", materials[i].shininess);
//        printf("  material.Ni = %f\n", materials[i].ior);
//        printf("  material.dissolve = %f\n", materials[i].dissolve);
//        printf("  material.illum = %d\n", materials[i].illum);
//        printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
//        printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
//        printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
//        printf("  material.map_Ns = %s\n", materials[i].normal_texname.c_str());
//        std::map::const_iterator it(materials[i].unknown_parameter.begin());
//        std::map::const_iterator itEnd(materials[i].unknown_parameter.end());
//        for (; it != itEnd; it++) {
//            printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
//        }
//        printf("\n");
//    }
//

    vertexBuffer->upload();
    return vertexBuffer;
}

ObjLoader::ObjLoader() {

}
