#pragma once

#include "Renderer.h"
#include "Transform.h"


class SpriteRenderer : public IRenderer
{
public:
	SpriteRenderer(glm::vec4 color = glm::vec4(1.0f));
	void Draw() override;
private:
	glm::vec4 spriteColor;
	GLuint VAO, shaderProgram;
};

