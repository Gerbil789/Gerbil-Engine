#include "ObjectManager.h"
#include <iostream>

size_t ObjectManager::objectId = 0;

ObjectManager::ObjectManager()
{
	//this->objects.resize(100);
	//std::fill(this->objects.begin(), this->objects.end(), nullptr);
}

GameObject* ObjectManager::Get(size_t id)
{
	auto obj = objects.find(id);
	if (obj != objects.end()) 
	{
		GameObject* foundObject = obj->second;
		return foundObject;
	}
	else 
	{
		return nullptr;
	}
}
void ObjectManager::Add(GameObject* object)
{
	size_t id = ObjectManager::objectId++;
	object->SetId(id);
	this->objects.emplace(id, object);
}


size_t ObjectManager::GetObjectCount()
{
	return this->objects.size();
}

void ObjectManager::UpdateObjects()
{
	for (const auto& pair : objects) {
		pair.second->Update();
	}
}




//WARNING: this find only one objects, even if there are multiple objects with same name
GameObject* ObjectManager::FindByName(std::string name)
{
	for (const auto& pair : objects) {
		if (pair.second->GetName() == name) {
			GameObject* foundObject = pair.second;
			return foundObject;
		}
	}
	return nullptr;
}


void ObjectManager::Dispose()
{
	for (const auto& pair : objects) {
		GameObject* object = pair.second;

		if (object != nullptr) {
			object->Dispose();
			delete object;
		}
	}
}

void ObjectManager::Remove(size_t id)
{
	GameObject* object = this->objects[id];

	this->objects.erase(id);
	object->Dispose();
	delete object;
}
