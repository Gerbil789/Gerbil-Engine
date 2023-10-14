#pragma once

#include "GameObject.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

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

