#include "Scene.h"
#include "../Components/MeshRenderer.h"
int Scene::sceneCount = 0;

Scene::Scene(const std::string& _name)
{
	sceneCount++;
	if (_name.empty())
	{
		name = "newScene" + std::to_string(sceneCount++);
	}
	else 
	{
		name = _name;
	}
}

void Scene::Init()
{
	for (GameObject* go : objectManager.GetObjects()) {
		if (MeshRenderer* meshRenderer = go->GetComponent<MeshRenderer>()) {
			Attach(meshRenderer);
		}
		
		if (CameraController* cameraController = go->GetComponent<CameraController>()) {
			cameraController->SetCam(GetActiveCamera());
		}

		
	}
}

void Scene::Update()
{
	objectManager.UpdateObjects();
}

std::string Scene::GetName()
{
	return name;
}


void Scene::Dispose()
{
	this->objectManager.Dispose();
}

void Scene::Add(GameObject* _object)
{
	objectManager.Add(_object);

	if (Light* light = _object->GetComponent<Light>()) {
		AddLight(light);
	}
}

ObjectManager& Scene::GetObjectManager()
{
	return this->objectManager;
}

void Scene::SetActiveCamera(Camera* _cam)
{
	activeCam = _cam;
}

Camera* Scene::GetActiveCamera()
{
	if (activeCam == nullptr) {
		for (GameObject* go : objectManager.GetObjects()) {
			
			if (Camera* cam = go->GetComponent<Camera>()) {
				SetActiveCamera(cam);
				return activeCam;
			}
		}
		
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
	Notify();
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
	Notify();
}

void Scene::Attach(IObserver* _observer)
{
	observers.push_back(_observer);
}

void Scene::Detach(IObserver* _observer)
{
	for (auto it = observers.begin(); it != observers.end(); ++it) {
		if (*it == _observer) {
			observers.erase(it);
			break;
		}
	}
}

void Scene::Notify()
{
	for (IObserver* observer : observers) {
		observer->UpdateObserver(this);
	}
}
