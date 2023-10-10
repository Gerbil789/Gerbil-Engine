#pragma once
#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"

class MeshRenderer : public IRenderer
{
public:
	MeshRenderer(glm::vec4 _color, std::string _model);
	void Draw() override;
	glm::vec4 color;
	Model* model;
private:
	GLuint shaderProgram;
};

