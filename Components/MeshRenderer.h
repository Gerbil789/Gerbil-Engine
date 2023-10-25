#pragma once

#include "../Components/Renderer.h"
#include "../GameObject/GameObject.h"
#include "../SceneManager.h"

#include "../Observer.h"

class Transform;

class MeshRenderer : public IRenderer, public IObserver
{
public:
	MeshRenderer(std::string _model = "sphere", glm::vec3 _color = glm::vec3(1.0f), std::string _shader = "phong", float _shininess = 16.0f);
	void Update() override;
	
	void SetTransform(Transform* t) override;
	void UpdateObserver() override; //update transformMatrix
private:
	GLuint shaderProgramId;
	Shader* shader;
	glm::mat4 transformMatrix;
	Model* model;
	glm::vec3 diffuse;
	float shininess;
};

