#ifndef MESH_H_INC
#define MESH_H_INC


#include "VertexBuffer.h"

class VertexBuffer;

class Mesh {


private:
	VertexBuffer* vertexBuffer;


public:
	VertexBuffer *getVertexBuffer() const {
		return vertexBuffer;
	}

	void setVertexBuffer(VertexBuffer *vertexBuffer) {
		this->vertexBuffer = vertexBuffer;
	}
public:
	Mesh();
	~Mesh();
};


#endif