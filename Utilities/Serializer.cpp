#include "Serializer.h"

void Serializer::SerializeToJson(Scene* _scene)
{
    json sceneData = SerializeScene(_scene);

    const std::string filePath = "Scenes/" + _scene->GetName() + ".json";

    std::ofstream outputFile(filePath);

    if (outputFile.is_open()) {
        outputFile << std::setw(4) << sceneData;
        outputFile.close();
        std::cout << "JSON data has been saved to " << filePath << "\n";
    }
    else {
        std::cerr << "Failed to open the file for writing." << "\n";
    }
}

Scene* Serializer::DeserializeFromJson(std::string path)
{
	return nullptr;
}

json Serializer::SerializeScene(Scene* _scene)
{
    json sceneData;
    sceneData["sceneName"] = _scene->GetName();
    json gameObjectsArray = json::array();

    for (GameObject* gameObject : _scene->GetObjectManager().GetObjects()) {
        if (gameObject->GetParent() == nullptr) {
            json gameObjectData = SerializeGameObject(gameObject);
            gameObjectsArray.push_back(gameObjectData);
        }
    }
    sceneData["gameObjects"] = gameObjectsArray;
    return sceneData;
}

json Serializer::SerializeGameObject(GameObject* _gameObject)
{
    json serializedGameObject;
    serializedGameObject["name"] = _gameObject->GetName();

    //transform
    serializedGameObject["transform"] = SerializeTransform(_gameObject->transform);


    //components
    json componentsArray;
    for (IComponent* component : _gameObject->GetComponents()) {
        componentsArray.push_back(SerializeComponent(component));
    }
    serializedGameObject["components"] = componentsArray;

    //children
    json childrenArray;
    for (GameObject* child : _gameObject->GetChildren()) {
        childrenArray.push_back(SerializeGameObject(child));
    }
    serializedGameObject["children"] = childrenArray;

    return serializedGameObject;
}

json Serializer::SerializeTransform(Transform* _transform)
{
    json serializedTransform;
    glm::vec3 pos = _transform->GetPosition();
    glm::quat rot = _transform->GetRotation();
    glm::vec3 sca = _transform->GetScale();
    serializedTransform["position"] = { pos.x, pos.y, pos.z };
    serializedTransform["rotation"] = { rot.w, rot.x, rot.y, rot.z };
    serializedTransform["scale"] = { sca.x, sca.y, sca.z };

    return serializedTransform;
}

json Serializer::SerializeComponent(IComponent* _component)
{
    json serializedComponent;
    std::string name = _component->GetName();
    serializedComponent["name"] = name;

    json componentsArray;
    if (name == "camera") {
        Camera* cam = dynamic_cast<Camera*>(_component);
        serializedComponent["fov"] = cam->GetFov();
        serializedComponent["aspect"] = cam->GetAspect();
        serializedComponent["nearPlane"] = cam->GetNearPlane();
        serializedComponent["farPlane"] = cam->GetFarPlane();
    }
    else if (name == "cameraController") {

    }
    else if (name == "light") {
        Light* light = dynamic_cast<Light*>(_component);
        serializedComponent["type"] = light->GetType();
        serializedComponent["intensity"] = light->GetIntensity();
        glm::vec3 col = light->GetColor();
        serializedComponent["color"] = { col.x, col.y, col.z };
    }
    else if (name == "meshRenderer") {

    }
    else {
        std::cout << "[NOT IMPLEMENTED] serialization component of type " << name << "\n";
    }

    return serializedComponent;
}
