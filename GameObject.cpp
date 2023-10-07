#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

GameObject::GameObject(std::string name)
{
	this->name = name;
	AddComponent<Transform>();
}


size_t GameObject::GetId()
{
	return this->id;
}

void GameObject::SetId(size_t id)
{
	this->id = id;
}

std::string GameObject::GetName()
{
	return this->name;
}

void GameObject::Dispose()
{
}
