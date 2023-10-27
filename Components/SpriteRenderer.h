#pragma once

#include "../Components/Renderer.h"
#include "../Engine/GameObject.h"


class SpriteRenderer : public IRenderer
{
public:
	SpriteRenderer(glm::vec3 color = glm::vec3(1.0f));
	void Update() override;
private:
	glm::vec3 spriteColor;
	GLuint VAO, shaderProgram;
};

