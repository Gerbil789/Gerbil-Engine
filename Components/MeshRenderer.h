#pragma once

#include "../Components/Renderer.h"
#include "../GameObject/GameObject.h"

#include "../Observer.h"

class Transform;

class MeshRenderer : public IRenderer, public IObserver
{
public:
	MeshRenderer(std::string _model = "sphere", glm::vec4 _color = glm::uvec4(1.0f), std::string _shader = "phong", float _specular = 16.0f);
	void Update() override;
	
	void SetTransform(Transform* t) override;
	void UpdateObserver() override; //update transformMatrix
private:
	GLuint shaderProgram;
	glm::mat4 transformMatrix;
	Model* model;
	glm::vec4 color;
	float specular;
};

