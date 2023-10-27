#include "MeshRenderer.h"
#include "../GameObject/Transform.h"

MeshRenderer::MeshRenderer(std::string _model, std::string _shader, Material* _material)
{
	componentName = "meshRenderer";

	material = _material;
	transformMatrix = glm::mat4(1.0f);
	shaderProgramId = ShaderManager::GetInstance().GetShaderProgramId(_shader);
	shader = shaderManager.GetShaderProgram(shaderProgramId);
	model = ModelManager::GetInstance().GetModel(_model);
	
	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }

	SetFlag(NORMAL);
	SetFlag(AMBIENT);
	SetFlag(DIFFUSE);
	SetFlag(SPECULAR);
	SetFlag(SHININESS);
	SetFlag(CAMERA);
	SetFlag(LIGHTS);

	SceneManager::GetInstance().GetActiveScene()->Attach(this);
}

void MeshRenderer::Update()
{
	shaderManager.UseShader(shaderProgramId);
	shaderManager.SetUniform("viewMatrix", shader->viewMatrix);
	shaderManager.SetUniform("projectionMatrix", shader->projectionMatrix);
	shaderManager.SetUniform("modelMatrix", transformMatrix);

	if (IsFlagSet(NORMAL)) {
		shaderManager.SetUniform("normalMatrix", glm::mat3(1.0f));
	}

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

			//glUniform1i(glGetUniformLocation(id, ("lights[" + std::to_string(i) + "].type").c_str()), lights[i].type);
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
		numLights = lights.size();
	}
}

void MeshRenderer::UpdateObserver()
{
	transformMatrix = transform->GetModel();
}


