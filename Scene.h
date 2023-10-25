#pragma once

#include "../Managers/ShaderManager.h"
#include "../Managers/ObjectManager.h"
#include "../Components/Camera.h"
#include "../Light.h"

class Scene
{
public:
	Scene(const std::string& _name = "");
	void Update();

	void Dispose();
	void Add(GameObject* _object);
	ObjectManager& GetObjectManager();

	void SetActiveCamera(Camera* _cam);
	Camera* GetActiveCamera();
	std::vector<Light*> GetLights();
	void AddLight(Light* _light);
	void RemoveLight(Light* _light);

private:
	static int sceneCount;
	std::string name;
	ObjectManager objectManager;
	Camera* activeCam;
	std::vector<Light*> lights;
	
};

