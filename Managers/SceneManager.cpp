#include "SceneManager.h"

void SceneManager::Init()
{

}

void SceneManager::SetActiveScene(Scene* _scene)
{
	activeScene = _scene;
}

Scene* SceneManager::GetActiveScene()
{
	if (activeScene == nullptr) {
		std::cerr << "ERROR: No active scene found.\n";
		exit(1);
	}
	return activeScene;
}

void SceneManager::AddScene(Scene* _scene)
{
	scenes.push_back(_scene);
	if (activeScene == nullptr) {
		activeScene = _scene;
	}
}
