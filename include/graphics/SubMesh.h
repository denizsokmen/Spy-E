#ifndef SUBMESH_H_INC
#define SUBMESH_H_INC

class Material;
class VertexBuffer;

class SubMesh {

public:
    VertexBuffer* vertexBuffer;
    Material* material;

    SubMesh();
    ~SubMesh();


};


#endif