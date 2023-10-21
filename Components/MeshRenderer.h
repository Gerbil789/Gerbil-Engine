#pragma once

#include "../Components/Renderer.h"
#include "../GameObject/GameObject.h"

#include "../Observer.h"

class Transform;

class MeshRenderer : public IRenderer, public IObserver
{
public:
	MeshRenderer(glm::vec4 _color, std::string _model);
	void Update() override;
	glm::vec4 color;
	Model* model;
	void SetTransform(Transform* t) override;
	void UpdateObserver() override;
private:
	Shader* shaderProgram;
	glm::mat4 transformMatrix;
};

