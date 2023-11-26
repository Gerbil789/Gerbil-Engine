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

	pointLights = std::vector<PointLight*>();
	directionalLights = std::vector<DirectionalLight*>();

	GameObject* skybox = new GameObject("skybox");
	Material* m_skybox = new Material("Textures/sky.jpg", "m_skybox");
	MeshRenderer* renderer =  skybox->AddComponent<MeshRenderer>("skydome", "texture", Color::White, m_skybox);
	//renderer->SetFlag(renderer->SKYBOX);
	SetSky(skybox);

}


void Scene::SetSky(GameObject* _sky)
{
	sky = _sky;
}

void Scene::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sky->transform->SetPosition(GetActiveCamera()->transform->GetPosition() + glm::vec3(0.0f, -0.25f, 0.0f));
	sky->Update();
	glClear(GL_DEPTH_BUFFER_BIT);

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

	if (PointLight* light = _object->GetComponent<PointLight>()) {
		pointLights.push_back(light);
		Notify();
	}else if (DirectionalLight* light = _object->GetComponent<DirectionalLight>()) {
		directionalLights.push_back(light);
		Notify();
	}
	else if (SpotLight* light = _object->GetComponent<SpotLight>()) {
		spotLights.push_back(light);
		Notify();
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


std::vector<PointLight*> Scene::GetPointLights()
{
	return pointLights;
}

std::vector<DirectionalLight*> Scene::GetDirectionalLights()
{
	return directionalLights;
}

std::vector<SpotLight*> Scene::GetSpotLights()
{
	return spotLights;
}



void Scene::RemoveLight(ILight* _light)
{
	/*lights.erase(
		std::remove_if(
			lights.begin(),
			lights.end(),
			[_light](ILight* ptr) { return ptr == _light; }
		),
		lights.end()
	);
	Notify();*/
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
