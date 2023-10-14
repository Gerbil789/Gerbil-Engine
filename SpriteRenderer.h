#pragma once

#include "Renderer.h"
#include "Transform.h"
#include "GameObject.h"


class SpriteRenderer : public IRenderer
{
public:
	SpriteRenderer(glm::vec4 color = glm::vec4(1.0f));
	void Update() override;
private:
	glm::vec4 spriteColor;
	GLuint VAO, shaderProgram;
};

