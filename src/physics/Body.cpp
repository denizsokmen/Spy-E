#include "physics/Body.h"

Body::Body(Entity* bodyEntity, std::vector<glm::vec3> v){

    this -> entity = bodyEntity;
    //this -> location = &bodyEntity->position;
    this -> speed = zeroVector;
    this -> acceleration = zeroVector;
    this -> vertices = v;
    boundingBox = new BoundingBox(vertices);
}

void Body::setLocation(glm::vec3 loc) {
	if (entity != NULL)
		entity->setPosition(loc);
    //*location = loc;
}

void Body::setSpeed(glm::vec3 s) {
    speed = s;
}

glm::vec3 Body::getAcceleration() {

    return acceleration;
}

glm::vec3 Body::getSpeed() {

    return speed;
}

glm::vec3 Body::getLocation(){
	if (entity != NULL)
		return entity->getPosition();

	return glm::vec3(0.0f, 0.0f, 0.0f);
}

BoundingBox* Body::getBoundingBox(){

    return boundingBox;
}

std::vector<glm::vec3> Body::getVertices() {
    return this->vertices;
}


void Body::setAcceleration(glm::vec3 acceleration) {
    this->acceleration = acceleration;
}

void Body::setAcceleration(float acceleration, char direction) {
    switch (direction) {
        case 'x':
            this->acceleration.x = acceleration;
            break;
        case 'y':
            this->acceleration.y = acceleration;
            break;
        case 'z':
            this->acceleration.z = acceleration;
            break;
        default:
            printf("No such direction!");
            break;
    }
}

void Body::setSpeed(float speed, char direction){
    switch (direction) {
        case 'x':
            this->speed.x = speed;
            break;
        case 'y':
            this->speed.y = speed;
            break;
        case 'z':
            this->speed.z = speed;
            break;
        default:
            printf("No such direction!");
            break;
    }
}

void Body::setLocation(float location, char direction) {
	if (entity != NULL) {
		glm::vec3 pos = entity->getPosition();
		switch (direction) {
		case 'x':
			entity->setPosition(glm::vec3(location, pos.y, pos.z));
			break;
		case 'y':
			entity->setPosition(glm::vec3(pos.x, location, pos.z));
			break;
		case 'z':
			entity->setPosition(glm::vec3(pos.x, pos.y, location));
			break;
		default:
			printf("No such direction!");
			break;
		}
	}
}

Body::~Body(){

}

void Body::addAcceleration(float acceleration, char direction) {
    switch (direction) {
        case 'x':
            this->acceleration.x += acceleration;
            break;
        case 'y':
            this->acceleration.y += acceleration;
            break;
        case 'z':
            this->acceleration.z += acceleration;
            break;
        default:
            printf("No such direction!");
            break;
    }
}

Entity *Body::getEntity() {
    return this->entity;
}

BoundingBox *Body::getBoundingBoxFromLocation() {

    std::vector<glm::vec3> tempVertices1 = this->vertices;

    for(int i = 0; i < tempVertices1.size(); i++){
		if (entity != NULL) {
			glm::vec3 pos = entity->getPosition();
			tempVertices1[i].x += pos.x;
			tempVertices1[i].y += pos.y;
			tempVertices1[i].z += pos.z;
		}
    }

    return new BoundingBox(tempVertices1);
}
