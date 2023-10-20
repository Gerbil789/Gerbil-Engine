#include "Scene.h"


Scene::Scene()
{

	
}

void Scene::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	objectManager.UpdateObjects();
}


void Scene::Dispose()
{
	this->objectManager.Dispose();
}

void Scene::Add(GameObject* object)
{
	this->objectManager.Add(object);
}

ObjectManager& Scene::GetObjectManager()
{
	return this->objectManager;
}

void Scene::SetActiveCamera(Camera* _cam)
{
	activeCam = _cam;
	ShaderManager::GetInstance().SetCamForShaders(activeCam);
}

Camera* Scene::GetActiveCamera()
{
	if (activeCam == nullptr) {
		std::cerr << "ERROR: No active camera found.\n";
	}
	return activeCam;
}
