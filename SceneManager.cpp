#include "SceneManager.h"

#include "../Scene.h"

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
	}
	return activeScene;
}

void SceneManager::AddScene(Scene* _scene)
{
	scenes.push_back(_scene);
}
