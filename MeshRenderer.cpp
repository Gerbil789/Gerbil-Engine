#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(glm::vec4 _color, std::string _model)
{
	this->color = _color;
	this->shaderProgram = ShaderManager::getInstance().GetShaderProgram("ModelShader");
	this->model = ModelManager::getInstance().GetModel(_model);

	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }
}

void MeshRenderer::Draw()
{
	//set shader program
	ShaderManager::getInstance().UseShader(shaderProgram);

	//set uniforms
	//transform
	GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
	if (idModelTransform == -1) {
		std::cout << "ERROR: could not find model transform location\n";
	}
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(transform->GetModel()));

	//viewMatrix
	GLint idView = glGetUniformLocation(shaderProgram, "viewMatrix");
	if (idView == -1) {
		std::cout << "ERROR: could not find viewMatrix location\n";
	}
	glUniformMatrix4fv(idView, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	//projectionMatrix
	GLint idProjection = glGetUniformLocation(shaderProgram, "projectionMatrix");
	if (idProjection == -1) {
		std::cout << "ERROR: could not find projectionMatrix location\n";
	}
	glUniformMatrix4fv(idProjection, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	//color
	GLint idColor = glGetUniformLocation(shaderProgram, "color");
	if (idColor == -1) {
		std::cerr << "Uniform not found in shader." << std::endl;
	}
	glUniform4fv(idColor, 1, glm::value_ptr(color));


	model->Draw();
}
