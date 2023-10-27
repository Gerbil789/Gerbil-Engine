#pragma once

#include "../Components/Renderer.h"
#include "../Engine/GameObject.h"
#include "../Managers/SceneManager.h"

#include "../Engine/Observer.h"

class Transform;

class MeshRenderer : public IRenderer, public IObserver
{
public:
	MeshRenderer(std::string _model = "sphere", std::string _shader = "phong", Material* _material = new Material());
	void Update() override;
	
	void SetTransform(Transform* t) override;
	void UpdateObserver(ISubject* _subject) override; //update transformMatrix
	void UpdateObserver() override; //update transformMatrix
private:
	GLuint shaderProgramId;
	Shader* shader;
	int numLights = 0;
	std::vector<Light*> lights;
	glm::mat4 transformMatrix;
	Model* model;
	Material* material;
};

