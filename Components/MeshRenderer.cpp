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
		SetFlag(COLOR);
	}
	else if (_shader == "lambert") {
		SetFlag(COLOR);
		SetFlag(AMBIENT);
		//SetFlag(DIFFUSE);
		SetFlag(LIGHTS);
	}
	else if (_shader == "phong" || _shader == "blinn") {
		SetFlag(COLOR);
		SetFlag(AMBIENT);
		//SetFlag(DIFFUSE);
		SetFlag(SPECULAR);
		SetFlag(SHININESS);
		SetFlag(CAMERA);
		SetFlag(LIGHTS);
		SetFlag(TEXTURE);
	}
	else if (_shader == "texture") {
		SetFlag(TEXTURE);
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
	if (IsFlagSet(COLOR)) {
		shaderManager.SetUniform("color", color);
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
		shaderManager.SetUniform("pointLightCount", pointLightCount);
		for (int i = 0; i < pointLightCount; i++) {
			shaderManager.SetUniform(("pointLights[" + std::to_string(i) + "].position").c_str(), pointLights[i]->transform->GetPosition());
			shaderManager.SetUniform(("pointLights[" + std::to_string(i) + "].color").c_str(), pointLights[i]->GetColor());
			shaderManager.SetUniform(("pointLights[" + std::to_string(i) + "].intensity").c_str(), pointLights[i]->GetIntensity());
		}

		shaderManager.SetUniform("directionalLightCount", directionalLightCount);
		for (int i = 0; i < directionalLightCount; i++) {
			shaderManager.SetUniform(("directionalLights[" + std::to_string(i) + "].color").c_str(), directionalLights[i]->GetColor());
			shaderManager.SetUniform(("directionalLights[" + std::to_string(i) + "].intensity").c_str(), directionalLights[i]->GetIntensity());
			shaderManager.SetUniform(("directionalLights[" + std::to_string(i) + "].direction").c_str(), directionalLights[i]->GetDirection());
		}

		shaderManager.SetUniform("spotLightCount", spotLightCount);
		for (int i = 0; i < spotLightCount; i++) {
			shaderManager.SetUniform(("spotLights[" + std::to_string(i) + "].position").c_str(), spotLights[i]->transform->GetPosition());
			shaderManager.SetUniform(("spotLights[" + std::to_string(i) + "].color").c_str(), spotLights[i]->GetColor());
			shaderManager.SetUniform(("spotLights[" + std::to_string(i) + "].intensity").c_str(), spotLights[i]->GetIntensity());
			shaderManager.SetUniform(("spotLights[" + std::to_string(i) + "].direction").c_str(), spotLights[i]->GetDirection());
			shaderManager.SetUniform(("spotLights[" + std::to_string(i) + "].innerConeAngle").c_str(), 20.0f);
			shaderManager.SetUniform(("spotLights[" + std::to_string(i) + "].outerConeAngle").c_str(), 30.0f);
		}
	}

	if (IsFlagSet(TEXTURE)) {
		//glActiveTexture(GL_TEXTURE0);
		if (IsFlagSet(SKYBOX)) {
			glBindTexture(GL_TEXTURE_CUBE_MAP, material->textureID);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, material->textureID);
		}


		GLint uniformID = glGetUniformLocation(shaderProgramId, "textureUnitID");
		if (uniformID == -1) {
			std::cout << "ERROR: could not find " << "textureUnitID" << " uniform\n";
		}
		glUniform1i(uniformID, 0);

		
	}

	
	
	//glBindTexture(GL_TEXTURE_2D, model->textureID);
	glBindVertexArray(model->VAO);
	glStencilFunc(GL_ALWAYS, gameObject->id, 0xFF);
	glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());

	glBindVertexArray(0);
	//model->Draw();
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
		pointLights = scene->GetPointLights();
		pointLightCount = (int)pointLights.size();

		directionalLights = scene->GetDirectionalLights();
		directionalLightCount = (int)directionalLights.size();

		spotLights = scene->GetSpotLights();
		spotLightCount = (int)spotLights.size();
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


