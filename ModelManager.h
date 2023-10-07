#pragma once

#include "Model.h"
#include <filesystem>
#include <map>

class ModelManager
{
public:
	static ModelManager& getInstance() {
		static ModelManager instance;
		return instance;
	}
	void Init();
	Model* GetModel(std::string _name);
private:
	ModelManager() {};
	std::map<std::string, Model*> models;
};
