#include "ModelManager.h"

void ModelManager::Init()
{
	for (const auto& entry : std::filesystem::directory_iterator("Models/")) {
		if (entry.is_regular_file() && entry.path().extension() == ".obj") {
			std::string path = entry.path().string();
			Model* model = new Model(path);
			this->models[model->name] = model;
		}
	}
}

Model* ModelManager::GetModel(std::string _name)
{
	auto it = models.find(_name);

	if (it != models.end()) {
		return it->second;
	}
	else {
		std::cerr << "ERROR: could not find model with name [" << _name << "]\n";
		return nullptr;
	}
}
