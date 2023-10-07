#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(glm::vec4 color)
{
	this->spriteColor = color;
	this->VAO = ShaderLib::getInstance().GetModelManager().GetModel("square")->VAO;
	this->shaderProgram = ShaderLib::getInstance().shaderPrograms[1].second;
}

void SpriteRenderer::Draw()
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
	glUniform4fv(uniformLocation, 1, glm::value_ptr(spriteColor));
	glBindVertexArray(VAO);

	// Draw the object
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// Unbind the VAO (optional but good practice)
	glBindVertexArray(0);
}
