#include "SceneManager.h"


void SceneManager::LoadScene(Scene* _scene)
{
	activeScene = _scene;
}

Scene* SceneManager::LoadScene(std::string _scene)
{
	const std::string filePath = "Scenes/" + _scene + ".json";
	activeScene = Serializer::DeserializeFromJson(filePath);
	//activeScene->Init();
	return activeScene;
}

void SceneManager::SaveScene()
{
	Serializer::SerializeToJson(activeScene);
}

Scene* SceneManager::GetActiveScene()
{
	if (activeScene == nullptr) {
		//std::cerr << "ERROR: No active scene found.\n";
		//exit(1);
	}
	return activeScene;
}


