#include "graphics/Renderable.h"
#include "graphics/Mesh.h"
#include <graphics/Animation.h>
#include "resource/ResourceManager.h"

Renderable::Renderable() {
	setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	mesh = NULL;
	animation = NULL;
	boneMatrix.resize(150, glm::mat4(1.0f));
}

void Renderable::update(float dt) {
	if (animation != NULL) {
		animation->update(dt);

		if (mesh->getSkeleton()) {
			for (unsigned int i = 0; i < mesh->getSkeleton()->bones.size(); i++) {
				boneMatrix[i] = animation->boneMatrix[i] * mesh->getSkeleton()->bones[i].inverseBindPose;
			}
		}
	}
}


void Renderable::addAnimation(std::string name, std::string filename) {
	if (animation == NULL)
		animation = new Animation();

	AnimationState* anim = ResourceManager::instance()->createAnimation(filename).get();

	if (anim != NULL) {
		animation->addState(name, anim);
	}
	else {
		printf("Error loading animation: %s\n", filename.c_str());
	}
}

void Renderable::setAnimation(std::string name) {
	if (animation != NULL)
		animation->setState(name);
}

VertexBuffer* Renderable::getVertexBuffer() {
    return mesh->getVertexBuffer();
}

Renderable::~Renderable() {

}

void Renderable::render(Renderer *renderer) {
    VertexBuffer *vertexBuffer = mesh->getVertexBuffer();
    vertexBuffer->bind();
    vertexBuffer->draw();
    vertexBuffer->unbind();
}
