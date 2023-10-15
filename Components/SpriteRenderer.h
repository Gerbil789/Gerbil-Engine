#pragma once

#include "../Components/Renderer.h"
#include "../GameObject/GameObject.h"


class SpriteRenderer : public IRenderer
{
public:
	SpriteRenderer(glm::vec4 color = glm::vec4(1.0f));
	void Update() override;
private:
	glm::vec4 spriteColor;
	GLuint VAO, shaderProgram;
};

