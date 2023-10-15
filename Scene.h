#pragma once

#include "../Managers/ShaderManager.h"
#include "../Managers/ObjectManager.h"
 

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

