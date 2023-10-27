#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

#include "../Engine/Observer.h"

class Transform: public ISubject
{
public:
	Transform(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
	void SetParentTransform(Transform* _transform);

	glm::mat4 GetModel() const;

	glm::vec3 GetPosition() const;
	glm::quat GetRotation() const;
	glm::vec3 GetScale() const;

	void SetPosition(const glm::vec3& position);
	void MoveBy(const glm::vec3& offset);

	void SetRotation(float angle, const glm::vec3& axis);
	void SetRotation(glm::quat quaternion);
	void RotateBy(float angle, const glm::vec3& axis);

	void SetScale(const glm::vec3& scale);
	void ScaleBy(const glm::vec3& scale);

	void Attach(IObserver* _observer) override;
	void Detach(IObserver* _observer) override;
	void Notify() override;
private:
	Transform* parentTransform = nullptr;
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;

	std::vector<IObserver*> observers;
};

