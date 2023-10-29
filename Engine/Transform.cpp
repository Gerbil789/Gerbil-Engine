#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void Transform::SetParentTransform(Transform* _transform)
{
	parentTransform = _transform;
	Notify();
}

glm::mat4 Transform::GetModel() const
{
	glm::mat4 model = glm::mat4(1.0f);
	if (parentTransform != nullptr) {
		model = parentTransform->GetModel();
	}
	
	model = glm::translate(model, this->position);
	model *= glm::mat4_cast(this->rotation);
	model = glm::scale(model, this->scale);

	return model;
}

glm::vec3 Transform::GetPosition() const
{
	return this->position;
}
glm::quat Transform::GetRotation() const
{
	return this->rotation;
}
glm::vec3 Transform::GetScale() const
{
	return this->scale;
}

void Transform::SetPosition(const glm::vec3& position)
{
	this->position = position;
	Notify();
}
void Transform::MoveBy(const glm::vec3& offset)
{
	this->position += offset;
	Notify();
}

void Transform::SetRotation(float angle, const glm::vec3& axis)
{
	if (angle == 0.0f) {
		return;
	}
	this->rotation = glm::rotate(glm::quat(), glm::radians(angle), axis);
	Notify();
}
void Transform::SetRotation(glm::quat quaternion)
{
	this->rotation = quaternion;
	Notify();
}
void Transform::RotateBy(float angle, const glm::vec3& axis)
{
	this->rotation = glm::rotate(rotation, glm::radians(angle), axis);
	Notify();
}

void Transform::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
	Notify();
}
void Transform::ScaleBy(const glm::vec3& scale)
{
	this->scale *= scale;
	Notify();
}


void Transform::Attach(IObserver* _observer)
{
	observers.push_back(_observer);
}

void Transform::Detach(IObserver* _observer)
{
	for (auto it = observers.begin(); it != observers.end(); ++it) {
		if (*it == _observer) {
			observers.erase(it);
			break;
		}
	}
}

void Transform::Notify()
{
	for (IObserver* observer : observers) {
		observer->UpdateObserver();
	}
}

