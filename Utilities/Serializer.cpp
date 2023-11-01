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

Scene* Serializer::DeserializeFromJson(const std::string& path)
{
    std::ifstream inputFile(path);
    if (inputFile.is_open()) {
        json sceneData;
        inputFile >> sceneData;

        Scene* scene = DeserializeScene(sceneData);
   
        inputFile.close();
        return scene;
    }
    else {
        std::cerr << "Failed to open the JSON file " << path << "\n";
    }
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
    glm::vec3 sca = _transform->GetScale();
    glm::quat rot = _transform->GetRotation();

    float ang = glm::degrees(2.0f * std::acos(rot.w));
    glm::vec3 dir = glm::vec3(rot.x, rot.y, rot.z);

    if (glm::length(dir) > 1e-6) {
        dir = glm::normalize(dir);
    }
    else {
        dir = glm::vec3(1.0f, 1.0f, 1.0f); 
    }

    serializedTransform["position"] = { pos.x, pos.y, pos.z };
    serializedTransform["rotation"] = { ang, dir.x, dir.y, dir.z };
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
        CameraController* cameraController = dynamic_cast<CameraController*>(_component);
        serializedComponent["speed"] = cameraController->GetSpeed();
    }
    else if (name == "light") {
       /* ILight* light = dynamic_cast<ILight*>(_component);
        serializedComponent["intensity"] = light->GetIntensity();
        glm::vec3 col = light->GetColor();
        serializedComponent["color"] = { col.x, col.y, col.z };*/
    }
    else if (name == "meshRenderer") {
        MeshRenderer* meshRenderer = dynamic_cast<MeshRenderer*>(_component);
        serializedComponent["shader"] = meshRenderer->GetShader()->name;
        serializedComponent["model"] = meshRenderer->GetModel()->name;
        serializedComponent["material"] = meshRenderer->GetMaterial()->name;
    }
    else if (name == "rotationScript") {
        RotationScript* rotationScript = dynamic_cast<RotationScript*>(_component);
        serializedComponent["value"] = rotationScript->val;
        glm::vec3 dir = rotationScript->dir;
        serializedComponent["direction"] = { dir.x, dir.y, dir.z };
    }
    else {
        std::cout << "[NOT IMPLEMENTED] serialization component of type " << name << "\n";
    }

    return serializedComponent;
}

//add childer go to a scene
void Serializer::AddGameObjectToScene(GameObject* _gameObject, Scene* _scene) {
    _scene->Add(_gameObject);
    for (GameObject* go : _gameObject->GetChildren()) {
        AddGameObjectToScene(go, _scene);
    } 
}

Scene* Serializer::DeserializeScene(const json& _sceneData)
{
    Scene* scene = new Scene(_sceneData["sceneName"]);
    const json& gameObjectsArray = _sceneData["gameObjects"];
    for (const json& gameObjectData : gameObjectsArray) {

        GameObject* gameObject = DeserializeGameObject(gameObjectData);
        AddGameObjectToScene(gameObject, scene); //recursion
    }

    return scene;
}



GameObject* Serializer::DeserializeGameObject(const json& _gameObjectData)
{
    std::string name = _gameObjectData["name"];

    GameObject* gameObject = new GameObject(name);
    gameObject->transform = DeserializeTransform(_gameObjectData["transform"]);

    //children
    if (_gameObjectData.find("children") != _gameObjectData.end() && !_gameObjectData["children"].is_null()) {
        for (const auto& childData : _gameObjectData["children"]) {
            GameObject* childObject = DeserializeGameObject(childData);
            gameObject->AddChildren(childObject);
        }
    }

    //components
    const json& componentsArray = _gameObjectData["components"];
    for (const auto& componentData : componentsArray) {
        DeserializeComponent(componentData, gameObject);
    }

    return gameObject;
}

Transform* Serializer::DeserializeTransform(const json& _transformObjectData)
{

    const json& positionArray = _transformObjectData["position"];
    glm::vec3 position(
        positionArray[0].get<float>(),
        positionArray[1].get<float>(),
        positionArray[2].get<float>()
    );

    const json& rotationArray = _transformObjectData["rotation"];
    float angle = rotationArray[0].get<float>(); //angle
	glm::vec3 dir(
		rotationArray[1].get<float>(), // x
		rotationArray[2].get<float>(), // y
		rotationArray[3].get<float>()  // z
	);

    const json& scaleArray = _transformObjectData["scale"];
    glm::vec3 scale(
        scaleArray[0].get<float>(),
        scaleArray[1].get<float>(),
        scaleArray[2].get<float>()
    );

    Transform* transform = new Transform();
    transform->SetPosition(position);
    transform->SetRotation(angle, dir);
    transform->SetScale(scale);

    return transform;
}

void Serializer::DeserializeComponent(const json& _componentData, GameObject* _gameObject)
{
    std::string name = _componentData["name"];

    if (name == "camera") {
        float fov = _componentData["fov"];
        float aspect = _componentData["aspect"];
        float nearPlane = _componentData["nearPlane"];
        float farPlane = _componentData["farPlane"];
        _gameObject->AddComponent<Camera>(fov, aspect, nearPlane, farPlane);
    }
    else if (name == "cameraController") {
        float speed = _componentData["speed"];
        _gameObject->AddComponent<CameraController>(speed); 
    }
    else if (name == "light") {
       /* int type = _componentData["type"];
        const json& positionArray = _componentData["color"];
        glm::vec3 color(
            positionArray[0].get<float>(),
            positionArray[1].get<float>(),
            positionArray[2].get<float>()
        );
        float intensity = _componentData["intensity"];

        _gameObject->AddComponent<ILight>(color, intensity);*/
    }
    else if (name == "meshRenderer") {
        std::string model = _componentData["model"];
        std::string shader = _componentData["shader"];
        std::string material = _componentData["material"];
        _gameObject->AddComponent<MeshRenderer>(model, shader);
    }
    else if (name == "rotationScript") {
        float val = _componentData["value"];
        const json& positionArray = _componentData["direction"];
        glm::vec3 dir(
            positionArray[0].get<float>(),
            positionArray[1].get<float>(),
            positionArray[2].get<float>()
        );
        _gameObject->AddComponent<RotationScript>(val, dir);
    }
    else {
        std::cout << "[NOT IMPLEMENTED] deserialization component\n";
    }
}

