#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <glm/glm.hpp>
#include <vector>


class VertexBuffer;
class Mesh;

class ObjLoader {


public:
        Mesh* loadOBJ(const char * path);
        ObjLoader();
};


#endif