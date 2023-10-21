#include "MeshRenderer.h"
#include "../GameObject/Transform.h"

MeshRenderer::MeshRenderer(glm::vec4 _color, std::string _model)
{
	this->color = _color;
	this->shaderProgram = ShaderManager::GetInstance().GetShaderProgram("phong");
	this->model = ModelManager::GetInstance().GetModel(_model);
	
	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }
	transformMatrix = glm::mat4(1.0f);
}

void MeshRenderer::Update()
{
	shaderProgram->UseShader(transformMatrix, color);

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


