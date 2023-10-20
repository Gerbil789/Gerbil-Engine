#pragma once
#include "../Scene.h"


class SceneManager
{
public:
	static SceneManager& GetInstance() {
		static SceneManager instance;
		return instance;
	}
	void SetActiveScene(Scene* _scene);
	Scene* GetActiveScene();
	void AddScene(Scene* _scene);

private:
	SceneManager() {};
	Scene* activeScene;
	std::vector<Scene*> scenes;
};

