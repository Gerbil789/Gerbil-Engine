#pragma once

#include <string>
#include <vector>

#include "../Engine/Transform.h"
#include "../Components/Component.h"

class GameObject
{
public:
	int id;
	GameObject(std::string name);
	void Update();
	std::string GetName();
	void Dispose();
	Transform* transform = new Transform();
	void AddChildren(GameObject* _child);
	void RemoveChildren(GameObject* _child);
	void SetParent(GameObject* _parent);
	GameObject* GetParent();
	std::vector<GameObject*> GetChildren();
	std::vector<IComponent*> GetComponents();

	template <typename T>
	void AddComponent() {
		T* newComponent = new T();
		newComponent->SetGameObject(this);
		newComponent->SetTransform(this->transform);
		components.push_back(newComponent);
	}

	template <typename T, typename... Args>
	T* AddComponent(Args... args) {
		T* newComponent = new T(args...);
		newComponent->SetGameObject(this);
		newComponent->SetTransform(this->transform);
		components.push_back(newComponent);
		return newComponent;
	}

	template <typename T>
	T* GetComponent() {
		for (IComponent* component : components) {
			if (dynamic_cast<T*>(component) != nullptr) {
				return static_cast<T*>(component);
			}
		}
		return nullptr;
	}

	

private:
	std::string name;
	std::vector<IComponent*> components;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
};

