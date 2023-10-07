#pragma once

#include "Model.h"
#include <vector>

class ModelManager
{
public:
	ModelManager();
	Model* GetModel(std::string _name);
	std::vector<Model*> models;
};

