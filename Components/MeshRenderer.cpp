#include "MeshRenderer.h"
#include "../Engine/Transform.h"

MeshRenderer::MeshRenderer(std::string _model, std::string _shader, glm::vec3 _color, Material* _material)
{
	componentName = "meshRenderer";

	color = _color;
	material = _material;
	transformMatrix = glm::mat4(1.0f);
	shaderProgramId = shaderManager.GetShaderProgramId(_shader);
	shader = shaderManager.GetShaderProgram(shaderProgramId);
	model = ModelManager::GetInstance().GetModel(_model);
	
	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }

	if (_shader == "constant") {

	}
	else if (_shader == "lambert") {
		SetFlag(AMBIENT);
		//SetFlag(DIFFUSE);
		SetFlag(LIGHTS);
	}
	else if (_shader == "phong" || _shader == "blinn") {
		SetFlag(AMBIENT);
		//SetFlag(DIFFUSE);
		SetFlag(SPECULAR);
		SetFlag(SHININESS);
		SetFlag(CAMERA);
		SetFlag(LIGHTS);
	}

	

	if (Scene* scene = SceneManager::GetInstance().GetActiveScene()) {
		scene->Attach(this);
	}
}

void MeshRenderer::Update()
{
	shaderManager.UseShader(shaderProgramId);
	shaderManager.SetUniform("viewMatrix", shader->viewMatrix);
	shaderManager.SetUniform("projectionMatrix", shader->projectionMatrix);
	shaderManager.SetUniform("modelMatrix", transformMatrix);
	shaderManager.SetUniform("color", color);

	if (IsFlagSet(AMBIENT)) {
		shaderManager.SetUniform("material.ambient", material->ambient);
	}

	if (IsFlagSet(DIFFUSE)) {
		shaderManager.SetUniform("material.diffuse", material->diffuse);
	}

	if (IsFlagSet(SPECULAR)) {
		shaderManager.SetUniform("material.specular", material->specular);
	}

	if (IsFlagSet(SHININESS)) {
		shaderManager.SetUniform("material.shininess", material->shininess);
	}

	if (IsFlagSet(CAMERA)) {
		shaderManager.SetUniform("cameraPosition", shader->camPosition);
	}

	if (IsFlagSet(LIGHTS)) {
		shaderManager.SetUniform("numLights", numLights);
		for (int i = 0; i < numLights; i++) {
			shaderManager.SetUniform(("lights[" + std::to_string(i) + "].position").c_str(), lights[i]->transform->GetPosition());
			shaderManager.SetUniform(("lights[" + std::to_string(i) + "].color").c_str(), lights[i]->GetColor());
			shaderManager.SetUniform(("lights[" + std::to_string(i) + "].intensity").c_str(), lights[i]->GetIntensity());
			
			//light type - not implemented
			//shaderManager.SetUniform(("lights[" + std::to_string(i) + "].type").c_str(), lights[i]->GetType());
		}
	}

	model->Draw();
}

void MeshRenderer::SetTransform(Transform* t)
{
	IComponent::SetTransform(t);
	transform->Attach(this);
	transformMatrix = transform->GetModel();
}

void MeshRenderer::UpdateObserver(ISubject* _subject)
{
	if (Scene* scene = dynamic_cast<Scene*>(_subject)) {
		lights = scene->GetLights();
		numLights = (int)lights.size();
	}
}

void MeshRenderer::UpdateObserver()
{
	transformMatrix = transform->GetModel();
}

void MeshRenderer::SetShader(std::string _shader)
{
	shaderProgramId = shaderManager.GetShaderProgramId(_shader);
	shader = shaderManager.GetShaderProgram(shaderProgramId);
}

Shader* MeshRenderer::GetShader()
{
	return shader;
}

void MeshRenderer::SetModel(std::string _model)
{
	model = ModelManager::GetInstance().GetModel(_model);
}

Model* MeshRenderer::GetModel()
{
	return model;
}

void MeshRenderer::SetMaterial(Material* _material)
{
	material = _material;
}

Material* MeshRenderer::GetMaterial()
{
	return material;
}


