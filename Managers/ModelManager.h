#pragma once

#include <filesystem>
#include <map>

#include "../Engine/Model.h"

class ModelManager
{
public:
	static ModelManager& GetInstance() {
		static ModelManager instance;
		return instance;
	}
	void Init();
	Model* GetModel(std::string _name);
private:
	ModelManager() {};
	std::map<std::string, Model*> models;
};

