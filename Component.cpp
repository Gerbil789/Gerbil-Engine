#include "Component.h"

void IComponent::SetGameObject(GameObject* go) {
  gameObject = go;
}


GameObject* IComponent::GetGameObject() {
	return this->gameObject;
}