#pragma once

#include "ShaderManager.h"
#include "ObjectManager.h"
 

class Scene
{
public:
	Scene();
	void Update();

	void Dispose();

	void Add(GameObject* object);

	ObjectManager& GetObjectManager();

private:
	ObjectManager objectManager;
};

