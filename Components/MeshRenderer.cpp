#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(glm::vec4 _color, std::string _model)
{
	this->color = _color;
	this->shaderProgram = ShaderManager::GetInstance().GetShaderProgram("phong");
	this->shaderId = shaderProgram->id;
	this->model = ModelManager::GetInstance().GetModel(_model);

	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }
}

void MeshRenderer::Update()
{
	shaderProgram->UseShader();

	//transformMatrix
	GLint idModelTransform = glGetUniformLocation(shaderId, "modelMatrix");
	if (idModelTransform == -1) {
		std::cout << "ERROR: could not find model transform location\n";
	}
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, glm::value_ptr(transform->GetModel()));

	//lightPos
	GLint idLight = glGetUniformLocation(shaderId, "lightPosition");
	if (idLight == -1) {
		std::cout << "ERROR: could not find lightPosition location\n";
	}
	glUniform3fv(idLight, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));

	//color
	GLint idColor = glGetUniformLocation(shaderId, "color");
	if (idColor == -1) {
		std::cerr << "Uniform color not found in shader." << std::endl;
	}
	glUniform4fv(idColor, 1, glm::value_ptr(color));

	model->Draw();
}


