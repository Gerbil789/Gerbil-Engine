#pragma once

#include "../Engine/Transform.h"
#include <string>

class GameObject;
class Transform;

class IComponent
{
public:
	virtual ~IComponent() {}

	virtual void Update() {}
	virtual void SetGameObject(GameObject* go);
	virtual void SetTransform(Transform* t);
	std::string GetName();

	GameObject* GetGameObject();
	GameObject* gameObject = nullptr;
	Transform* transform = nullptr;
protected:
	std::string componentName = "undefinedComponent";

	
};

