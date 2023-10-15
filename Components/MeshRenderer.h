#pragma once

#include "../Components/Renderer.h"
#include "../GameObject/GameObject.h"

class MeshRenderer : public IRenderer
{
public:
	MeshRenderer(glm::vec4 _color, std::string _model);
	void Update() override;
	glm::vec4 color;
	Model* model;
private:
	GLuint shaderProgram;
};

