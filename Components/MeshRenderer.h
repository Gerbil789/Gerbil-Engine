#pragma once

#include "../Components/Renderer.h"
#include "../Engine/GameObject.h"
#include "../Managers/SceneManager.h"

#include "../Engine/Observer.h"

class Transform;

class MeshRenderer : public IRenderer, public IObserver
{
public:
	MeshRenderer(std::string _model = "sphere", std::string _shader = "phong", glm::vec3 _color = Color::White, Material* _material = new Material());
	void Update() override;
	void SetTransform(Transform* t) override;
	void UpdateObserver(ISubject* _subject) override; 
	void UpdateObserver() override;

	void SetShader(std::string _shader);
	Shader* GetShader();
	void SetModel(std::string _model);
	Model* GetModel();
	void SetMaterial(Material* _material);
	Material* GetMaterial();

private:
	GLuint shaderProgramId;
	Shader* shader;
	int numLights = 0;
	std::vector<Light*> lights;
	glm::mat4 transformMatrix;
	Model* model;
	Material* material;
	glm::vec3 color;
};

