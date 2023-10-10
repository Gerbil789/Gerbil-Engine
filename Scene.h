#pragma once

#include "ShaderManager.h"
#include "ObjectManager.h"
 

class Scene
{
public:
	Scene();
	void Draw();

	void Dispose();

	void Add(GameObject* object);

	ObjectManager& GetObjectManager();

private:
	ObjectManager objectManager;
};

