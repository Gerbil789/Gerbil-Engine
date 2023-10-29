#pragma once

#include <vector>
#include "../Engine/Scene.h"
#include "../Utilities/Serializer.h"

class SceneManager
{
public:
	static SceneManager& GetInstance() {
		static SceneManager instance;
		return instance;
	}

	void LoadScene(Scene* _scene); //load from code
	Scene* LoadScene(std::string _scene);	//load from file
	void SaveScene(); //save to file

	Scene* GetActiveScene();

private:
	SceneManager() {};
	Scene* activeScene = nullptr;
};

