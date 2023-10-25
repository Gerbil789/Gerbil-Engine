#include "Scene.h"

int Scene::sceneCount = 0;

Scene::Scene(const std::string& _name)
{
	sceneCount++;
	if (name.empty()) 
	{
		name = "newScene" + std::to_string(sceneCount++);
	}
	else 
	{
		name = _name;
	}
}

void Scene::Update()
{
	objectManager.UpdateObjects();
}


void Scene::Dispose()
{
	this->objectManager.Dispose();
}

void Scene::Add(GameObject* _object)
{
	objectManager.Add(_object);

	if (Light* light = _object->GetComponent<Light>()) {
		lights.push_back(light);
	}
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


std::vector<Light*> Scene::GetLights()
{
	return lights;
}

void Scene::AddLight(Light* _light)
{
	lights.push_back(_light);
}

void Scene::RemoveLight(Light* _light)
{
	lights.erase(
		std::remove_if(
			lights.begin(),
			lights.end(),
			[_light](Light* ptr) { return ptr == _light; }
		),
		lights.end()
	);
}
