#include "../Managers/SceneManager.h"
#include "GameObject.h"


int GameObject::nextID = 5;

GameObject::GameObject(std::string name)
{
	//to do: make id pool or something... (255 limit)
	if (name == "tree" || name == "sphere") {
		id = 3;
	}
	else {
		this->id = nextID++;
	}

	//std::cout << "ID: " << id << "\n";
	
	this->name = name;
	this->transform = new Transform();
}

void GameObject::Update()
{
	if (destroy) {
		countdown -= Time::deltaTime;
		if (countdown <= 0.0f) {
			Destroy();
		}
	}

	for (IComponent* component : components) {
		component->Update();
	}
}

void GameObject::Destroy()
{
	SceneManager::GetInstance().GetActiveScene()->GetObjectManager().Remove(this);

	delete this;
}

void GameObject::Destroy(float t)
{
	countdown = t;
	destroy = true;
}


std::string GameObject::GetName()
{
	return this->name;
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

GameObject* GameObject::GetParent()
{
	return parent;
}

std::vector<GameObject*> GameObject::GetChildren()
{
	return children;
}

std::vector<IComponent*> GameObject::GetComponents()
{
	return components;
}
