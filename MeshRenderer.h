#pragma once
#include "Renderer.h"
#include "Transform.h"

class MeshRenderer : public IRenderer
{
public:
	MeshRenderer(glm::vec4 _color);
	void Draw() override;
	glm::vec4 color;
private:
	GLuint VAO, shaderProgram;

};

