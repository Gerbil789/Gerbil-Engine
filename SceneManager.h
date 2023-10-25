#pragma once

#include <vector>
#include "../Scene.h"

class SceneManager
{
public:
	static SceneManager& GetInstance() {
		static SceneManager instance;
		return instance;
	}
	void Init();
	void SetActiveScene(Scene* _scene);
	Scene* GetActiveScene();
	void AddScene(Scene* _scene);

private:
	SceneManager() {};
	Scene* activeScene = nullptr;
	std::vector<Scene*> scenes;
};

