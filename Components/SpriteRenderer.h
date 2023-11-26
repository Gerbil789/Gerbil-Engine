#pragma once

#include "../Components/Renderer.h"
#include "../Engine/GameObject.h"



class SpriteRenderer : public IRenderer, public IObserver
{
public:
	SpriteRenderer(std::string _texture = "Textures/coin.png", glm::vec3 _color = Color::White);
	void Update() override;

	void SetTransform(Transform* t) override;
	void UpdateObserver() override; //update transfrom

private:
	GLuint shaderProgramId;
	Shader* shader;
	GLuint textureId;
	glm::mat4 transformMatrix;
	Model* model;
	glm::vec3 color;
};

