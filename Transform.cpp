#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}




glm::mat4 Transform::getModel() const
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
	model *= glm::mat4_cast(this->rotation);
	model = glm::scale(model, this->scale);

	return model;
}

glm::vec3 Transform::getPosition() const
{
	return this->position;
}
glm::quat Transform::getRotation() const
{
	return this->rotation;
}
glm::vec3 Transform::getScale() const
{
	return this->scale;
}

void Transform::setPosition(const glm::vec3& position)
{
	this->position = position;
}
void Transform::moveBy(const glm::vec3& offset)
{
	this->position += offset;
}

void Transform::setRotation(float angle, const glm::vec3& axis)
{
	this->rotation = glm::rotate(glm::quat(), glm::radians(angle), axis);
}
void Transform::setRotation(glm::quat quaternion)
{
	this->rotation = quaternion;
}
void Transform::rotateBy(float angle, const glm::vec3& axis)
{
	this->rotation = glm::rotate(rotation, glm::radians(angle), axis);
}

void Transform::setScale(const glm::vec3& scale)
{
	this->scale = scale;
}
void Transform::scaleBy(const glm::vec3& scale)
{
	this->scale *= scale;
}

