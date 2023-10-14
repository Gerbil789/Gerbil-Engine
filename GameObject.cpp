#include "GameObject.h"
#include "Component.h"
#include "Transform.h"

GameObject::GameObject(std::string name)
{
	this->name = name;
	this->transform = new Transform();
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

void GameObject::AddChildren(GameObject* _child)
{
	children.push_back(_child);
	_child->transform->SetParentTransform(this->transform);
	_child->SetParent(this);
}

void GameObject::RemoveChildren(GameObject* _child)
{
	auto it = std::find(children.begin(), children.end(), _child);

	if (it != children.end()) {
		_child->SetParent(nullptr);
		_child->transform->SetParentTransform(nullptr);
		children.erase(it);
	}
}

void GameObject::SetParent(GameObject* _parent)
{
	if (parent != nullptr) {
		parent->RemoveChildren(this);
		this->transform->SetParentTransform(nullptr);
	}
	parent = _parent;
}
