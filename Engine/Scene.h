#pragma once

#include "../Managers/ShaderManager.h"
#include "../Managers/ObjectManager.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Engine/Observer.h"

class Scene : public ISubject
{
public:
	Scene(const std::string& _name = "");
	void Update();
	std::string GetName();

	void Dispose();
	void Add(GameObject* _object);
	ObjectManager& GetObjectManager();

	void SetActiveCamera(Camera* _cam);
	Camera* GetActiveCamera();
	std::vector<Light*> GetLights();
	void AddLight(Light* _light);
	void RemoveLight(Light* _light);

	void Attach(IObserver* _observer) override;
	void Detach(IObserver* _observer) override;
	void Notify() override;
private:
	static int sceneCount;
	std::string name;
	ObjectManager objectManager;
	Camera* activeCam;
	std::vector<Light*> lights;
	std::vector<IObserver*> observers; //mesh renderers
	
};

