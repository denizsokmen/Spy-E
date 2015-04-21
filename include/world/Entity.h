

#ifndef _SPYE_ENTITY_H_
#define _SPYE_ENTITY_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

class Entity {
private:

	glm::vec3 position;
	glm::vec3 pivot;
	glm::quat orientation;
	glm::mat4 transformation;
	glm::vec3 color;
	glm::vec3 scale;
protected:

public:
    std::string name;
    

    Entity();
    virtual ~Entity() {};
	glm::mat4 getTransformation() const;
	void setTransformation(glm::mat4& trans);

    glm::quat getOrientation() const;
    void setOrientation(glm::quat &orientation);

    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 &position);

	glm::vec3 getColor() const;
	void setColor(glm::vec3 &color);

	glm::vec3 getScale() const;
	void setScale(glm::vec3 &scale);

	void updateTransformation();



};

#endif
