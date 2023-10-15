#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(glm::vec4 color)
{
	this->spriteColor = color;
	this->VAO = ModelManager::GetInstance().GetModel("cube")->VAO;
	this->shaderProgram = ShaderManager::GetInstance().GetShaderProgram("ModelShader");
}

void SpriteRenderer::Update()
{
	
}
