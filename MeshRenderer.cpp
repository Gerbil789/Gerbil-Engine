#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(glm::vec4 _color, const char* _model)
{
	this->color = _color;
	this->shaderProgram = ShaderManager::getInstance().shaderPrograms[1].second;
	this->model = ModelManager::getInstance().GetModel(_model);

	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }
}

void MeshRenderer::Draw()
{
	//TO DO: move this somewhere else :d


	//set shader program
	ShaderManager::getInstance().UseShader(shaderProgram);


	//set transform
	GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
	if (idModelTransform == -1) {
		std::cout << "ERROR: could not find model transform location\n";
	}
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(transform->GetModel()));

	//set color
	
	GLint uniformLocation = glGetUniformLocation(shaderProgram, "color");
	if (uniformLocation == -1) {
		std::cerr << "Uniform not found in shader." << std::endl;
	}
	glUniform4fv(uniformLocation, 1, glm::value_ptr(color));
	
	model->Draw();
	
}
