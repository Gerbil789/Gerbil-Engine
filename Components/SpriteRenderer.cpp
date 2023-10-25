#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(glm::vec3 color)
{
	this->spriteColor = color;
	this->VAO = ModelManager::GetInstance().GetModel("cube")->VAO;
	//this->shaderProgram = ShaderManager::GetInstance().GetShaderProgram("ModelShader");
}

void SpriteRenderer::Update()
{
	
}
