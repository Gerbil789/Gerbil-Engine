#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(glm::vec4 _color, std::string _model)
{
	this->color = _color;
	this->shaderProgram = ShaderManager::GetInstance().GetShaderProgram("lambert");
	this->model = ModelManager::GetInstance().GetModel(_model);

	if (model == nullptr) { std::cerr << "[MeshRemderer] ERROR: could not load model [" << _model << "]\n"; }
}

void MeshRenderer::Update()
{
	//set shader program
	ShaderManager::GetInstance().UseShader(shaderProgram);

	//set uniforms
	//transformMatrix
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
	glm::mat4 tmp = ShaderManager::GetInstance().GetCam()->CalculateViewMatrix();
	glUniformMatrix4fv(idView, 1, GL_FALSE, glm::value_ptr(tmp));

	//projectionMatrix
	GLint idProjection = glGetUniformLocation(shaderProgram, "projectionMatrix");
	if (idProjection == -1) {
		std::cout << "ERROR: could not find projectionMatrix location\n";
	}
	tmp = ShaderManager::GetInstance().GetCam()->CalculateProjectionMatrix();
	glUniformMatrix4fv(idProjection, 1, GL_FALSE, glm::value_ptr(tmp));


	//normalMatrix
	GLint idNormal = glGetUniformLocation(shaderProgram, "normalMatrix");
	if (idNormal == -1) {
		std::cout << "ERROR: could not find normalMatrix location\n";
	}
	glUniformMatrix3fv(idNormal, 1, GL_FALSE, glm::value_ptr(glm::mat3(1.0f)));

	//lightPos
	GLint idLight = glGetUniformLocation(shaderProgram, "lightPosition");
	if (idLight == -1) {
		std::cout << "ERROR: could not find lightPosition location\n";
	}
	glUniform3fv(idLight, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));


	//color
	GLint idColor = glGetUniformLocation(shaderProgram, "color");
	if (idColor == -1) {
		std::cerr << "Uniform color not found in shader." << std::endl;
	}
	glUniform4fv(idColor, 1, glm::value_ptr(color));


	model->Draw();
}
