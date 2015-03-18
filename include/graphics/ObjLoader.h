#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <glm/glm.hpp>
#include <vector>


class VertexBuffer;

class ObjLoader {


public:
        VertexBuffer* loadOBJ(const char * path);
        ObjLoader();
};


#endif