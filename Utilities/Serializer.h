#pragma once

#include <nlohmann/json.hpp>
#include "../Engine/Scene.h"
#include "../Components/Camera.h"
#include "../Components/CameraController.h"
#include "../Components/MeshRenderer.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/Light.h"
using json = nlohmann::json;

class Serializer
{
public:
	static void SerializeToJson(Scene* _scene);
	static Scene* DeserializeFromJson(const std::string& path);
private:
	static json SerializeScene(Scene* _scene);
	static json SerializeGameObject(GameObject* _gameObject);
	static json SerializeTransform(Transform* _transform);
	static json SerializeComponent(IComponent* _component);

	static Scene* DeserializeScene(const json& _sceneData);
	static GameObject* DeserializeGameObject(const json& _gameObjectData);
	static Transform* DeserializeTransform(const json& _transformObjectData);
	static void DeserializeComponent(const json& _componentData, GameObject* _gameObject);
};

