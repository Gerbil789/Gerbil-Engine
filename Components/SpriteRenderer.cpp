#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(std::string _texture, glm::vec3 _color)
{
	color = _color;

	shaderProgramId = shaderManager.GetShaderProgramId("sprite");
	shader = shaderManager.GetShaderProgram(shaderProgramId);

	model = ModelManager::GetInstance().GetModel("plane");
	transformMatrix = glm::mat4(1.0f);

	textureId = Material::LoadTexture(_texture);
}

void SpriteRenderer::Update()
{
	shaderManager.UseShader(shaderProgramId);
	shaderManager.SetUniform("viewMatrix", shader->viewMatrix);
	shaderManager.SetUniform("projectionMatrix", shader->projectionMatrix);
	shaderManager.SetUniform("modelMatrix", transformMatrix);
	shaderManager.SetUniform("color", color);
	

	glBindTexture(GL_TEXTURE_2D, textureId);
		

	GLint uniformID = glGetUniformLocation(shaderProgramId, "textureUnitID");
	if (uniformID == -1) {
		std::cout << "ERROR: could not find " << "textureUnitID" << " uniform\n";
	}
	glUniform1i(uniformID, 0);



	glBindVertexArray(model->VAO);
	glStencilFunc(GL_ALWAYS, gameObject->id, 0xFF);
	glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());

	glBindVertexArray(0);
	//model->Draw();
}

void SpriteRenderer::SetTransform(Transform* t)
{
	IComponent::SetTransform(t);
	transform->Attach(this);
	transformMatrix = transform->GetModel();
}

void SpriteRenderer::UpdateObserver()
{
	transformMatrix = transform->GetModel();
}
