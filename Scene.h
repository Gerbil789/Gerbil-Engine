#pragma once

#include "../Managers/ShaderManager.h"
#include "../Managers/ObjectManager.h"
#include "../Components/Camera.h"

class Scene
{
public:
	Scene();
	void Update();

	void Dispose();
	void Add(GameObject* object);
	ObjectManager& GetObjectManager();

	void SetActiveCamera(Camera* _cam);
	Camera* GetActiveCamera();

private:
	std::string name = "scene";
	ObjectManager objectManager;
	Camera* activeCam;
	
};

