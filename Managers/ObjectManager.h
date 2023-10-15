#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

#include "../GameObject/GameObject.h"

class ObjectManager
{
public:
	ObjectManager();

	GameObject* Get(size_t id);

	void Add(GameObject* object);
	void Remove(size_t id);

	size_t GetObjectCount();
	void UpdateObjects();

	GameObject* FindByName(std::string name);

	void Dispose();

private:
	static size_t objectId;
	std::unordered_map<size_t, GameObject*> objects;
};

