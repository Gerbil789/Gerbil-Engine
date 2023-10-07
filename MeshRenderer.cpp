#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(glm::vec4 _color)
{
	this->color = _color;
	this->VAO = ShaderLib::getInstance().GetModelManager().GetModel("cube")->VAO;
	this->shaderProgram = ShaderLib::getInstance().shaderPrograms[1].second;
}

void MeshRenderer::Draw()
{
	Transform* transform = gameObject->GetComponent<Transform>();
	ShaderLib::getInstance().UseShader(shaderProgram);

	GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
	if (idModelTransform == -1) {
		std::cout << "ERROR: could not find model transform location\n";
	}
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(transform->getModel()));


	GLint uniformLocation = glGetUniformLocation(shaderProgram, "color");
	if (uniformLocation == -1) {
		std::cerr << "Uniform not found in shader." << std::endl;
	}
	glUniform4fv(uniformLocation, 1, glm::value_ptr(color));
	glBindVertexArray(VAO);

	// Draw the object
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Unbind the VAO (optional but good practice)
	glBindVertexArray(0);
}
