#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Component.h"
#include "GameObject.h"

class Transform : public IComponent
{
public:
	Transform(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

	glm::mat4 getModel() const;

	glm::vec3 getPosition() const;
	glm::quat getRotation() const;
	glm::vec3 getScale() const;

	void setPosition(const glm::vec3& position);
	void moveBy(const glm::vec3& offset);

	void setRotation(float angle, const glm::vec3& axis);
	void setRotation(glm::quat quaternion);
	void rotateBy(float angle, const glm::vec3& axis);

	void setScale(const glm::vec3& scale);
	void scaleBy(const glm::vec3& scale);

private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
};

