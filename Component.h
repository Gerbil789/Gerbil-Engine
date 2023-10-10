#pragma once


class GameObject;
class Transform;


class IComponent
{
public:
	virtual ~IComponent() {}

	virtual void Update() {}
	virtual void SetGameObject(GameObject* go);
	virtual void SetTransform(Transform* t);

	GameObject* GetGameObject();

protected:
	GameObject* gameObject;
	Transform* transform;
};

