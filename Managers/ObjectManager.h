#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

#include "../Engine/GameObject.h"

class ObjectManager
{
public:
	ObjectManager();
	void UpdateObjects();

	void Add(GameObject* _object);
	void Remove(GameObject* _object);
	size_t GetObjectCount();
	std::vector<GameObject*> GetObjects();
	GameObject* FindByName(std::string _name);

	void Dispose();

private:
	std::vector<GameObject*> objects;
};

