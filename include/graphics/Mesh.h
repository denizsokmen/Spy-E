#ifndef MESH_H_INC
#define MESH_H_INC


#include "VertexBuffer.h"
#include "Skeleton.h"


class VertexBuffer;
class SubMesh;
class Material;

class Mesh {
friend class SubMesh;

private:
	VertexBuffer* vertexBuffer;


public:
	Material* material;

	VertexBuffer *getVertexBuffer();

	void setVertexBuffer(VertexBuffer *vertexBuffer) {
		this->vertexBuffer = vertexBuffer;
	}
public:
	Mesh();
	~Mesh();
	std::vector<SubMesh*> subMeshes;

	void setSkeleton(Skeleton * skeleton);

	Skeleton *getSkeleton();
	Skeleton *skeleton;
	std::vector<glm::mat4> boneMatrix;
};


#endif
