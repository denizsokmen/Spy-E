

#include "world/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

Entity::Entity() {
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
	pivot = glm::vec3(0,0,0);
	//orientation = glm::quat(0,0,0,1);
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

void Entity::setRotation(glm::vec3&& rotation){
	printf("Rotation: x:%f, y:%f, z:%f\n", rotation.x, rotation.y, rotation.z);
//
	float PI = glm::pi<float>();
	//this->setOrientation(glm::rotate(this->getOrientation(), PI, glm::vec3(0.0f, 0.0f, 1.0f)));
//	this->setOrientation(glm::rotate(this->getOrientation(), PI/4.0f, glm::vec3(1.0f, 0.0f, 0.0f)));
//	glm::quat rota = glm::angleAxis(-halfPI, glm::vec3(1.0f,0.0f,0.0f));

	this->setOrientation(glm::rotate(this->getOrientation(), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)));
	this->setOrientation(glm::rotate(this->getOrientation(), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)));
	this->setOrientation(glm::rotate(this->getOrientation(), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)));

//	this->orientation = glm::normalize ( orientation);

//	glm::quat rot1 = glm::angleAxis(rotation.x, glm::vec3(1.0f,0.0f,0.0f));
//	glm::quat rot2 = glm::angleAxis(rotation.y, glm::vec3(0.0f,1.0f,0.0f));
//	glm::quat rot3 = glm::angleAxis(rotation.z, glm::vec3(0.0f,0.0f,1.0f));

	//this->setOrientation(rot1 * rot2 * rot3);

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
	transformation = glm::translate(glm::mat4(1.0f), position)
					 * glm::translate(glm::mat4(1.0f), pivot * -1.0f)
					 * glm::toMat4(orientation)
					 * glm::scale(glm::mat4(1.0), scale)
					 * glm::translate(glm::mat4(1.0f), pivot);
}

void Entity::setName(std::string name) {
	this->name = name;
}
