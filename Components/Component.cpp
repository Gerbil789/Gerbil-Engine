#include "Component.h"

void IComponent::SetGameObject(GameObject* go) {
  gameObject = go;
}

void IComponent::SetTransform(Transform* t) {
  transform = t;
}

std::string IComponent::GetName()
{
	return componentName;
}


GameObject* IComponent::GetGameObject() {
	return this->gameObject;
}