#include "ObjectManager.h"
#include <iostream>

size_t ObjectManager::objectId = 0;

ObjectManager::ObjectManager()
{

}

void ObjectManager::Add(GameObject* _object)
{
	size_t id = ObjectManager::objectId++;
	_object->SetId(id);
	objects.push_back(_object);
}


size_t ObjectManager::GetObjectCount()
{
	return this->objects.size();
}

std::vector<GameObject*> ObjectManager::GetObjects()
{
	return objects;
}

void ObjectManager::UpdateObjects()
{
	for (GameObject* ptr : objects) {
		ptr->Update();
	}
}

GameObject* ObjectManager::FindByName(std::string _name)
{
	for (GameObject* ptr : objects) {
		if (ptr->GetName() == _name) {
			return ptr;
		}
	}
	return nullptr;
}

void ObjectManager::Dispose()
{
	for (GameObject* ptr : objects) {
		ptr->Dispose();
		delete ptr;
	}
}

void ObjectManager::Remove(GameObject* _object)
{
	objects.erase(
		std::remove_if(
			objects.begin(),
			objects.end(),
			[_object](GameObject* ptr) { return ptr == _object; }
		),
		objects.end()
	);
}
