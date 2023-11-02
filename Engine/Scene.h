#pragma once

#include "../Managers/ShaderManager.h"
#include "../Managers/ObjectManager.h"
#include "../Components/Camera.h"
#include "../PointLight.h"
#include "../DirectionalLight.h"
#include "../SpotLight.h"


class Scene : public ISubject
{
public:
	Scene(const std::string& _name = "");
	void Init(); //call after scene is loaded
	void Update();
	std::string GetName();

	void Dispose();
	void Add(GameObject* _object);
	ObjectManager& GetObjectManager();

	void SetActiveCamera(Camera* _cam);
	Camera* GetActiveCamera();

	std::vector<PointLight*> GetPointLights();
	std::vector<DirectionalLight*> GetDirectionalLights();
	std::vector<SpotLight*> GetSpotLights();


	void RemoveLight(ILight* _light);

	void Attach(IObserver* _observer) override;
	void Detach(IObserver* _observer) override;
	void Notify() override;
private:
	static int sceneCount;
	std::string name;
	ObjectManager objectManager;
	Camera* activeCam;
	std::vector<PointLight*> pointLights;
	std::vector<DirectionalLight*> directionalLights;
	std::vector<SpotLight*> spotLights;
	std::vector<IObserver*> observers; //mesh renderers
	
};

