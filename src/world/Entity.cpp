

#include "world/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Entity::Entity() {
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::mat4 Entity::getTransformation() const {

	//transformation = glm::translate(glm::mat4(1.0f), position);// *glm::translate(glm::mat4(1.0f), pivot*-1.0f) * glm::toMat4(orientation) * glm::scale(glm::mat4(1.0), scale) * glm::translate(glm::mat4(1.0f), pivot);
	/* transformation[3][0] = position[0];
	transformation[3][1] = position[1];
	transformation[3][2] = position[2];*/
	return transformation;
}

void Entity::setTransformation(glm::mat4&& trans) {
	orientation = glm::normalize(glm::toQuat(trans));
	position = glm::vec3(trans[3]);
}

glm::quat Entity::getOrientation() const {
    return orientation;
}

void Entity::setOrientation(glm::quat&& orientation) {
	if (this->orientation != orientation) {
		this->orientation = orientation;
		updateTransformation();
	}

}

glm::vec3 Entity::getPosition() const {
    return position;
}

void Entity::setPosition(glm::vec3&& position) {
	if (this->position != position) {

		this->position = position;

		updateTransformation();
	}
}

glm::vec3 Entity::getColor() const {
	return color;
}

void Entity::setColor(glm::vec3&& color) {
	if (this->color != color)
		updateTransformation();
	this->color = color;
}

glm::vec3 Entity::getScale() const {
	return scale;
}

void Entity::setScale(glm::vec3&& scale) {
	if (this->scale != scale) {

		this->scale = scale;
		updateTransformation();
	}

}

void Entity::updateTransformation() {
	transformation = glm::translate(glm::mat4(1.0f), position) *glm::translate(glm::mat4(1.0f), pivot*-1.0f) * glm::toMat4(orientation) * glm::scale(glm::mat4(1.0), scale) * glm::translate(glm::mat4(1.0f), pivot);
}