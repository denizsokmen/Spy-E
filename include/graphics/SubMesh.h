#ifndef SUBMESH_H_INC
#define SUBMESH_H_INC

class Material;
class VertexBuffer;
class Mesh;

class SubMesh {

public:

    int triangleCount;
    int indexOffset;

    Mesh* mesh;
    VertexBuffer* vertexBuffer;
    VertexBuffer *getVertexBuffer();
    void setVertexBuffer(VertexBuffer *vertexBuffer);
    Material *getMaterial();
    void setMaterial(Material *material);

    Material* material;

    SubMesh();
    ~SubMesh();


};


#endif