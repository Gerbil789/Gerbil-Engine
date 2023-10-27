#pragma once

#include "../GameObject/Transform.h"
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
	GameObject* gameObject;
	Transform* transform;
protected:
	std::string componentName = "undefinedComponent";

	
};

