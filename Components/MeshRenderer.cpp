#include "MeshRenderer.h"
#include "../GameObject/Transform.h"

MeshRenderer::MeshRenderer(std::string _model, glm::vec4 _color, std::string _shader, float _specular)
{
	color = _color;
	specular = _specular;
	transformMatrix = glm::mat4(1.0f);
	shaderProgram = ShaderManager::GetInstance().GetShaderProgram(_shader);
	model = ModelManager::GetInstance().GetModel(_model);
	
	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }
}

void MeshRenderer::Update()
{
	ShaderManager::GetInstance().UseShader(shaderProgram, transformMatrix, color, specular);
	model->Draw();
}

void MeshRenderer::SetTransform(Transform* t)
{
	IComponent::SetTransform(t);
	transform->Attach(this);
	transformMatrix = transform->GetModel();
}

void MeshRenderer::UpdateObserver()
{
	transformMatrix = transform->GetModel();
}


