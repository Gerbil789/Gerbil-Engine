#pragma once

class GameObject;


class IComponent
{
public:
	virtual ~IComponent() {}

	virtual void SetGameObject(GameObject* go);

	GameObject* GetGameObject();

protected:
	GameObject* gameObject;
};

